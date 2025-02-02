#include "renderer.hpp"

#include <algorithm>

#include <imgui.h>
#include <GLFW/glfw3.h>

Renderer::Renderer()
    : mCamera(width, height, mView, mProjection)
{
    CreateFramebuffer();
}

Renderer::~Renderer()
{
    DestroyFramebuffer();
}

Vector3 Renderer::ApplyRenderingPipeline(const Vector3 &p)
{
    Vector4 coords = Vector4(p.x, p.y, p.z, 1.0f);

    Matrix4x4 mat = mProjection * mView * ModelMatrix;
    coords = coords * mat;

    coords /= coords.w;

    return Vector3(
        (width / 2) * (coords.x + 1),
        (height / 2) * (coords.y + 1),
        coords.z / 2 + 0.5f
    );
}

void Renderer::SetPixel(const unsigned int x, const unsigned int y)
{
    mColorBuffer[y * width + x] = 1;
}

void Renderer::SetPixel(const unsigned int x, const unsigned int y, const Vector4& color)
{
    mColorBuffer[y * width + x] = color;
}

void Renderer::DrawTriangles(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Texture& texture)
{
    const Vector2i min(
        (int) std::clamp(std::min(std::min(v1.Position.x, v2.Position.x), v3.Position.x), 0.f, (float) width),
        (int) std::clamp(std::min(std::min(v1.Position.y, v2.Position.y), v3.Position.y), 0.f, (float) height)
    );
    const Vector2i max(
        (int) std::clamp(std::max(std::max(v1.Position.x, v2.Position.x), v3.Position.x), 0.f, (float) width),
        (int) std::clamp(std::max(std::max(v1.Position.y, v2.Position.y), v3.Position.y), 0.f, (float) height)
    );

    for (int x = min.x; x < max.x; x++)
        for (int y = min.y; y < max.y; y++)
        {
            const float denominator = (v2.Position.y - v3.Position.y) * (v1.Position.x - v3.Position.x)
                + (v3.Position.x - v2.Position.x) * (v1.Position.y - v3.Position.y);
            // Just in case, to avoid division by zero
            if (denominator == 0)
                continue;

            const float weight1 = ((v2.Position.y - v3.Position.y) * (x - v3.Position.x)
                + (v3.Position.x - v2.Position.x) * (y - v3.Position.y)) / denominator;
            if (weight1 < 0)
                continue;

            const float weight2 = ((v3.Position.y - v1.Position.y) * (x - v3.Position.x)
                + (v1.Position.x - v3.Position.x) * (y - v3.Position.y)) / denominator;
            if (weight2 < 0)
                continue;

            const float weight3 = 1 - weight1 - weight2;
            if (weight3 < 0)
                continue;

            const unsigned int index = y * width + x;
            const float depth = v1.Position.z * weight1 + v2.Position.z * weight2 + v3.Position.z * weight3;
            if (depth < mDepthBuffer[index])
                mDepthBuffer[index] = depth;
            else
                continue;

            Vector4 color = v1.Color * weight1 + v2.Color * weight2 + v3.Color * weight3;

            const Vector2 uv = v1.UVs * weight1 + v2.UVs * weight2 + v3.UVs * weight3;
            color *= texture.Sample(uv);

            SetPixel(x, y, color);
        }
}

void Renderer::PreRender()
{
    mCamera.Update();

    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
        {
            unsigned int index = y * width + x;
            mColorBuffer[index] = 0;
            mDepthBuffer[index] = INFINITY;
        }
}

void Renderer::Render(const std::vector<Vertex> &vertices, const Texture &texture)
{
    std::vector<Vertex> transformed(vertices);
    for (size_t i = 0; i < vertices.size(); i++)
        transformed[i].Position = ApplyRenderingPipeline(vertices[i].Position);

    for (size_t i = 0; i < vertices.size(); i += 3)
        DrawTriangles(
            transformed[i],
            transformed[i + 1],
            transformed[i + 2],
            texture
        );
}

void Renderer::PostRender()
{
    UpdateFramebuffer();
}

void Renderer::CreateFramebuffer()
{
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glEnable(GL_TEXTURE_2D);
}

void Renderer::UpdateFramebuffer()
{
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, mColorBuffer);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);

    glTexCoord2f(0, 0);
    glVertex2f(-1, 1);
    glTexCoord2f(0, 1);
    glVertex2f(-1, -1);
    glTexCoord2f(1, 1);
    glVertex2f(1, -1);
    glTexCoord2f(1, 0);
    glVertex2f(1, 1);

    glEnd();
    glFlush();
}

void Renderer::DestroyFramebuffer()
{
    glDeleteTextures(1, &mTextureID);
}
