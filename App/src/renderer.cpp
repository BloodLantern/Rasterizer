#include "renderer.hpp"

#include <cassert>
#include <cmath>

#define COLOR_BUFFER_POS(x, y) (m_Width * (y) + (x))

Renderer::Renderer(unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height)
{
    m_ColorBuffer = new Vector4[width * height];
    m_DepthBuffer = new float_t[width * height];
}

Renderer::~Renderer()
{
    delete[] m_ColorBuffer;
    delete[] m_DepthBuffer;
}

void Renderer::SetProjectionMatrix(const Matrix4x4& projection)
{
    m_Projection = projection;
}

void Renderer::SetViewMatrix(const Matrix4x4& view)
{
    m_View = view;
}

void Renderer::SetModelMatrix(const Matrix4x4& model)
{
    m_Model = model;
}

void Renderer::SetViewportMatrix(const Matrix4x4& viewport)
{
    m_Viewport = viewport;
}

void Renderer::SetViewportMatrix(const Vector2 position, const Vector2 size)
{
    // TODO
}

void Renderer::SetPixel(const unsigned int x, const unsigned int y)
{
    m_ColorBuffer[COLOR_BUFFER_POS(x, y)] = Vector4(1);
}

void Renderer::SetPixel(const unsigned int x, const unsigned int y, const Vector4& color)
{
    m_ColorBuffer[COLOR_BUFFER_POS(x, y)] = color;
}

void Renderer::DrawLine(unsigned int x0, unsigned int y0, const unsigned int x1, const unsigned int y1)
{
    int dx = std::abs((int)(x1 - x0));
    int sx = x0 < x1 ? 1 : -1;
    int dy = std::abs((int)(y1 - y0));
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    for (;;)
    {
        SetPixel(x0, y0);

        if (x0 == x1 && y0 == y1)
            break;

        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void Renderer::DrawLine(unsigned int x0, unsigned int y0, const unsigned int x1, const unsigned int y1, const Vector4& color)
{
    int dx = std::abs((int)(x1 - x0));
    int sx = x0 < x1 ? 1 : -1;
    int dy = std::abs((int)(y1 - y0));
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    for (;;)
    {
        SetPixel(x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}

/*
void rdrSetTexture(rdrImpl* renderer, float* colors32Bits, int width, int height)
{
    assert(renderer != nullptr);
    // TODO(later): Store
}

void rdrDrawTriangles(rdrImpl* renderer, rdrVertex* vertices, int count)
{
    assert(renderer != nullptr);

    // For each triangles
    // TODO: Convert vertex local coords to screen coords
    // TODO: Draw triangle with lines (using drawLine)
    // Transform vertex list to triangle into colorBuffer
}
*/
