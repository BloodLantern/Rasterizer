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
    std::vector<Vertex> mVertices;
    Texture mTexture;
    Texture mModelTexture;
    Model mModel;
};
