#pragma once

#include <vector>

#include <matrix4x4.hpp>
#include <vector2.hpp>
#include <vector2i.hpp>

#include "vertex.hpp"
#include "texture.hpp"

constexpr unsigned int width = 800;
constexpr unsigned int height = 600;

class Renderer
{
private:
    Texture mTexture;
    unsigned int mTextureID;

    Vector4 mColorBuffer[width * height];
    float mDepthBuffer[width * height];

    Matrix4x4 mView;
    Matrix4x4 mProjection;
    Matrix4x4 mModel = Matrix4x4::Identity();

    void CreateFramebuffer();
    void UpdateFramebuffer();
    void DestroyFramebuffer();

public:
    Renderer();
    ~Renderer();

    Vector3 ApplyRenderingPipeline(const Vector3& p);

    void SetPixel(const uint32_t x, const uint32_t y);
    void SetPixel(const uint32_t x, const uint32_t y, const Vector4& color);

    void DrawTriangle(Vector3 p1, const Vector3 p2, const Vector3 p3, const Vertex& v1, const Vertex& v2, const Vertex& v3);

    // Draw a list of triangles
    void Render(const std::vector<Vertex>& vertices);
};

/*
// Texture setup
RENDERER_API void rendererSetTexture(rendererImpl* renderer, float* colors32Bits, int width, int height);

struct ImGuiContext;
RENDERER_API void rendererSetImGuiContext(rendererImpl* renderer, struct ImGuiContext* context);
RENDERER_API void rendererShowImGuiControls(rendererImpl* renderer);
*/
