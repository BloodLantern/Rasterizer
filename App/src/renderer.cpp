#include "renderer.hpp"

#include <cassert>
#include <numbers>
#include <iostream>

#include <imgui.h>
#include <GLFW/glfw3.h>

Renderer::Renderer()
    : mTexture("assets/texture.jpeg")
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

void Renderer::SetPixel(const uint32_t x, const uint32_t y)
{
    mColorBuffer[y * width + x] = 1;
}

void Renderer::SetPixel(const uint32_t x, const uint32_t y, const Vector4& color)
{
    mColorBuffer[y * width + x] = color;
}

void Renderer::DrawTriangle(Vector3 p1, const Vector3 p2, const Vector3 p3, const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
    for (unsigned int x = 0; x < width; x++)
        for (unsigned int y = 0; y < height; y++)
        {
            const float denominator = (p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y);

            const float w1 = ((p2.y - p3.y) * (x - p3.x) + (p3.x - p2.x) * (y - p3.y)) / denominator;
            if (w1 < 0 || w1 > 1)
                continue;

            const float w2 = ((p3.y - p1.y) * (x - p3.x) + (p1.x - p3.x) * (y - p3.y)) / denominator;
            if (w2 < 0 || w2 > 1)
                continue;

            const float w3 = 1 - w1 - w2;
            if (w3 < 0 || w3 > 1)
                continue;

            Vector4 color = v1.Color * w1 + v2.Color * w2 + v3.Color * w3;

            const Vector2 uv = v1.UVs * w1 + v2.UVs * w2 + v3.UVs * w3;
            color *= mTexture.Sample(uv);

            SetPixel(x, y, color);
        }
}

float currentTime = 0.0f;

void Renderer::Render(const std::vector<Vertex> &vertices)
{
    currentTime += ImGui::GetIO().DeltaTime;

    mModel = Matrix4x4::TRS(0, Vector3(0, currentTime, currentTime * 3), 1);
    Matrix4x4::ViewMatrix(Vector3(0.f, 0.f, 2.f), 0, Vector3::UnitY(), mView);
    Matrix4x4::ProjectionMatrix((float) std::numbers::pi / 2, width / (float) height, 0.1f, 100.f, mProjection);

    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            mColorBuffer[y * width + x] = 0;

    std::vector<Vector3> transformed = std::vector<Vector3>(vertices.size());
    for (size_t i = 0; i < vertices.size(); i++)
    {
        transformed[i] = ApplyRenderingPipeline(vertices[i].Position);
    }


    for (size_t i = 0; i < vertices.size(); i++)
    {
        Vector3 p1 = transformed[i];
        Vector3 p2 = transformed[(i + 1) % vertices.size()];
        Vector3 p3 = transformed[(i + 2) % vertices.size()];

        DrawTriangle(p1, p2, p3, vertices[i], vertices[(i + 1) % vertices.size()], vertices[(i + 2) % vertices.size()]);
    }

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
    ImGui::Image(ImTextureID(mTextureID), ImVec2(width, height));
}

void Renderer::DestroyFramebuffer()
{
    glDeleteTextures(1, &mTextureID);
}

/*
void rendererSetTexture(rendererImpl* renderer, float* colors32Bits, int width, int height)
{
    assert(renderer != nullptr);
    // TODO(later): Store
}
*/
