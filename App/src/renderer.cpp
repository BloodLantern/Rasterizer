#include "renderer.hpp"

#include <cassert>
#include <numbers>
#include <iostream>
#include <algorithm>

#include <imgui.h>
#include <GLFW/glfw3.h>

Renderer::Renderer()
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

    Matrix4x4 mat = mProjection * mView * mModel;
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

void Renderer::DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Texture& texture)
{
    const Vector2i min(
        (int) std::clamp(std::min(std::min(v1.Position.x, v2.Position.x), v3.Position.x), 0.f, width - 1.f),
        (int) std::clamp(std::min(std::min(v1.Position.y, v2.Position.y), v3.Position.y), 0.f, height - 1.f)
    );
    const Vector2i max(
        (int) std::clamp(std::max(std::max(v1.Position.x, v2.Position.x), v3.Position.x), 0.f, width - 1.f),
        (int) std::clamp(std::max(std::max(v1.Position.y, v2.Position.y), v3.Position.y), 0.f, height - 1.f)
    );

    for (int x = min.x; x < max.x; x++)
        for (int y = min.y; y < max.y; y++)
        {
            const float denominator = (v2.Position.y - v3.Position.y) * (v1.Position.x - v3.Position.x)
                + (v3.Position.x - v2.Position.x) * (v1.Position.y - v3.Position.y);
            if (denominator == 0)
                continue;

            const float w1 = ((v2.Position.y - v3.Position.y) * (x - v3.Position.x)
                + (v3.Position.x - v2.Position.x) * (y - v3.Position.y)) / denominator;
            if (w1 < 0 || w1 > 1)
                continue;

            const float w2 = ((v3.Position.y - v1.Position.y) * (x - v3.Position.x)
                + (v1.Position.x - v3.Position.x) * (y - v3.Position.y)) / denominator;
            if (w2 < 0 || w2 > 1)
                continue;

            const float w3 = 1 - w1 - w2;
            if (w3 < 0 || w3 > 1)
                continue;

            const unsigned int index = y * width + x;
            const float depth = v1.Position.z * w1 + v2.Position.z * w2 + v3.Position.z * w3;
            if (depth < mDepthBuffer[index])
                mDepthBuffer[index] = depth;
            else
                continue;

            Vector4 color = v1.Color * w1 + v2.Color * w2 + v3.Color * w3;

            const Vector2 uv = v1.UVs * w1 + v2.UVs * w2 + v3.UVs * w3;
            color *= texture.Sample(uv);

            SetPixel(x, y, color);
        }
}

void Renderer::Render(const std::vector<Vertex> &vertices, const Texture& texture)
{
    mModel = Matrix4x4::TRS(0, Vector3(0), 1);
    Matrix4x4::ViewMatrix(Vector3(0.f, 0.f, 2.f), 0, Vector3::UnitY(), mView);
    Matrix4x4::ProjectionMatrix((float) std::numbers::pi / 2, width / (float) height, mNear, mFar, mProjection);

    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
        {
            unsigned int index = y * width + x;
            mColorBuffer[index] = 0;
            mDepthBuffer[index] = INFINITY;
        }

    std::vector<Vertex> transformed(vertices);
    for (size_t i = 0; i < vertices.size(); i++)
        transformed[i].Position = ApplyRenderingPipeline(vertices[i].Position);

    for (size_t i = 0; i < vertices.size(); i++)
        DrawTriangle(
            transformed[i],
            transformed[(i + 1) % transformed.size()],
            transformed[(i + 2) % transformed.size()],
            texture
        );

    UpdateFramebuffer();
}

void Renderer::CreateFramebuffer()
{
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Renderer::UpdateFramebuffer()
{
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, mColorBuffer);
    ImGui::Image((ImTextureID) mTextureID, ImVec2(width, height));
}

void Renderer::DestroyFramebuffer()
{
    glDeleteTextures(1, &mTextureID);
}
