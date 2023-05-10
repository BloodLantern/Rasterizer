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

    void Update(Renderer& renderer);
    void ShowImGuiControls();

private:
    char mTexturePath[MaxFilepathLength] = "assets/gradient.png";
    char mModelTexturePath[MaxFilepathLength] = "assets/mountain_texture.png";
    char mModelPath[MaxFilepathLength] = "assets/mountain.obj";

    Vector3 mWorldPosition = 0;
    Vector3 mWorldRotation = 0;
    Vector3 mWorldScale = 1;

    std::vector<Vertex> mVertices;
    Texture mTexture;
    Texture mModelTexture;
    Model mModel;
};
