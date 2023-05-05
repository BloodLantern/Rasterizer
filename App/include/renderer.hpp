#pragma once

#include <matrix4x4.hpp>
#include <vector2.hpp>
#include <vector2i.hpp>

#include <random>

#include "vertex.hpp"

constexpr unsigned int width = 8;
constexpr unsigned int height = 12;

class Renderer
{
private:
    std::default_random_engine mRandomDevice;
    std::uniform_real_distribution<float> mRandomFloat;

    unsigned int mTextureID;

    Vector4 mColorBuffer[width][height];
    float mDepthBuffer[width][height];

    Matrix4x4 mProjection;
    Matrix4x4 mView;
    Matrix4x4 mModel;
    Matrix4x4 mViewport;

public:
    Renderer();
    ~Renderer();

    void SetProjectionMatrix(const Matrix4x4& projection);
    void SetViewMatrix(const Matrix4x4& view);
    void SetModelMatrix(const Matrix4x4& model);
    void SetViewportMatrix(const Matrix4x4& viewport);
    void SetViewportMatrix(const Vector2& position, const Vector2& size);

    void SetPixel(const Vector2i& position);
    void SetPixel(const Vector2i& position, const Vector4& color);

    void DrawLine(Vector2i p1, const Vector2i& p2);
    void DrawLine(Vector2i p1, const Vector2i& p2, const Vector4& color);

    // Draw a list of triangles
    void DrawTriangles(Vertex* vertices, int vertexCount);

    void CreateFramebuffer();
    void UpdateFramebuffer();
    void DestroyFramebuffer();
};

/*
// Texture setup
RENDERER_API void rendererSetTexture(rendererImpl* renderer, float* colors32Bits, int width, int height);

struct ImGuiContext;
RENDERER_API void rendererSetImGuiContext(rendererImpl* renderer, struct ImGuiContext* context);
RENDERER_API void rendererShowImGuiControls(rendererImpl* renderer);
*/
