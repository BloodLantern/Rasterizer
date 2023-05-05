#include "renderer.hpp"

#include <cassert>

#include <imgui.h>
#include <GLFW/glfw3.h>

Renderer::Renderer()
    : mRandomDevice(std::random_device()()),
    mRandomFloat(0, 1)
{
}

Renderer::~Renderer()
{
}

void Renderer::SetProjectionMatrix(const Matrix4x4& projection)
{
    mProjection = projection;
}

void Renderer::SetViewMatrix(const Matrix4x4& view)
{
    mView = view;
}

void Renderer::SetModelMatrix(const Matrix4x4& model)
{
    mModel = model;
}

void Renderer::SetViewportMatrix(const Matrix4x4& viewport)
{
    mViewport = viewport;
}

void Renderer::SetViewportMatrix(const Vector2& position, const Vector2& size)
{
    // TODO
}

void Renderer::SetPixel(const Vector2i& position)
{
    mColorBuffer[position.x][position.y] = 1;
}

void Renderer::SetPixel(const Vector2i& position, const Vector4& color)
{
    mColorBuffer[position.x][position.y] = color;
}

void Renderer::DrawLine(Vector2i p1, const Vector2i& p2)
{
    int dx = std::abs(p2.x - p1.x);
    int sx = p1.x < p2.x ? 1 : -1;
    int dy = std::abs(p2.y - p1.y);
    int sy = p1.y < p2.y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (true)
    {
        SetPixel(p1.x, p1.y);

        if (p1.x == p2.x && p1.y == p2.y)
            break;

        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            p1.x += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            p1.y += sy;
        }
    }
}

void Renderer::DrawLine(Vector2i p1, const Vector2i& p2, const Vector4& color)
{
    int dx = std::abs(p2.x - p1.x);
    int sx = p1.x < p2.x ? 1 : -1;
    int dy = std::abs(p2.y - p1.y);
    int sy = p1.y < p2.y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (true)
    {
        SetPixel(p1, color);

        if (p1.x == p2.x && p1.y == p2.y)
            break;

        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            p1.x += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            p1.y += sy;
        }
    }
}

void Renderer::DrawTriangles(Vertex* vertices, int count)
{
    // For each triangles
    // TODO: Convert vertex local coords to screen coords
    // TODO: Draw triangle with lines (using drawLine)
    // Transform vertex list to triangle into colorBuffer
}

void Renderer::CreateFramebuffer()
{
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Renderer::UpdateFramebuffer()
{
    //float random = mRandomFloat(mRandomDevice);
    // TODO: Apply framebuffer to the texture

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
