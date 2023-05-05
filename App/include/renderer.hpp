#pragma once

#include <matrix4x4.hpp>
#include <vector2.hpp>

class Renderer
{
private:
    unsigned int m_Width;
    unsigned int m_Height;

    Vector4* m_ColorBuffer;
    float* m_DepthBuffer;

    Matrix4x4 m_Projection;
    Matrix4x4 m_View;
    Matrix4x4 m_Model;
    Matrix4x4 m_Viewport;

public:
    Renderer(unsigned int width, unsigned int height);
    ~Renderer();

    void SetProjectionMatrix(const Matrix4x4& projection);
    void SetViewMatrix(const Matrix4x4& view);
    void SetModelMatrix(const Matrix4x4& model);
    void SetViewportMatrix(const Matrix4x4& viewport);
    void SetViewportMatrix(const Vector2 position, const Vector2 size);

    void SetPixel(const unsigned int x, const unsigned int y);
    void SetPixel(const unsigned int x, const unsigned int y, const Vector4& color);

    void DrawLine(const unsigned int x0, const unsigned int y0, const unsigned int x1, const unsigned int y1);
    void DrawLine(const unsigned int x0, const unsigned int y0, const unsigned int x1, const unsigned int y1, const Vector4& color);
};

/*
// Texture setup
RDR_API void rdrSetTexture(rdrImpl* renderer, float* colors32Bits, int width, int height);

// Draw a list of triangles
RDR_API void rdrDrawTriangles(rdrImpl* renderer, rdrVertex* vertices, int vertexCount);

struct ImGuiContext;
RDR_API void rdrSetImGuiContext(rdrImpl* renderer, struct ImGuiContext* context);
RDR_API void rdrShowImGuiControls(rdrImpl* renderer);
*/
