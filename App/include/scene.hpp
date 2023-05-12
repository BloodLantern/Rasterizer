#pragma once

#include <vector>

#include "vertex.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "model.hpp"

constexpr unsigned int MaxFilepathLength = 40;

class Scene
{
public:
    Scene();

    void AddTriangle(const Vector3& p1, const Vector3& p2, const Vector3& p3);

    void Update(Renderer& renderer);
    void ShowImGuiControls();

private:
    char mTexturePath[MaxFilepathLength] = "assets/gradient.png";
    char mModelTexturePath[MaxFilepathLength] = "assets/mountain/buildings_texture.png";
    char mModelPath[MaxFilepathLength] = "assets/mountain/buildings.obj";
    char mMountainModelTexturePath[MaxFilepathLength] = "assets/mountain/mountain_texture.png";
    char mMountainModelPath[MaxFilepathLength] = "assets/mountain/mountain.obj";

    Vector3 mWorldPosition = 0;
    Vector3 mWorldRotation = 0;
    Vector3 mWorldScale = Vector3(1, 1, -1);

    std::vector<Vertex> mTriangleVertices;
    Texture mTexture;
    Texture mMountainModelTexture;
    Model mMountainModel;
    Texture mModelTexture;
    Model mModel;
};
