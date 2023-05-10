#pragma once

#include <vector>

#include "vertex.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "model.hpp"

class Scene
{
public:
    Scene();

    void Update(Renderer& renderer);
    void ShowImGuiControls();

private:
    std::string mTexturePath = "assets/gradient.png";
    std::string mModelTexturePath = "assets/mountain_texture.png";
    std::string mModelPath = "assets/mountain.obj";

    Vector3 mWorldPosition = 0;
    Vector3 mWorldRotation = 0;
    Vector3 mWorldScale = 1;

    std::vector<Vertex> mVertices;
    Texture mTexture;
    Texture mModelTexture;
    Model mModel;
};
