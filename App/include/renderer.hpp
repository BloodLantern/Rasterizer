#pragma once

#include <vector>

#include <vector2.hpp>
#include <vector2i.hpp>

#include "vertex.hpp"
#include "texture.hpp"
#include "camera.hpp"

constexpr unsigned int width = 800;
constexpr unsigned int height = 600;

class Renderer
{
private:
    unsigned int mTextureID;

    Vector4 mColorBuffer[width * height];
    float mDepthBuffer[width * height];

    Camera mCamera;

    Matrix4x4 mView;
    Matrix4x4 mProjection;

    void CreateFramebuffer();
    void UpdateFramebuffer();
    void DestroyFramebuffer();

public:
    Matrix4x4 ModelMatrix = Matrix4x4::Identity();

    Renderer();
    ~Renderer();

    Vector3 ApplyRenderingPipeline(const Vector3& p);

    void SetPixel(const unsigned int x, const unsigned int y);
    void SetPixel(const unsigned int x, const unsigned int y, const Vector4& color);

    void DrawTriangles(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Texture& texture);

    void PreRender();
    void Render(const std::vector<Vertex>& vertices, const Texture& texture);
    void PostRender();
};
