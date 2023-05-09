#pragma once

#include <vector>

#include "vertex.hpp"
#include "renderer.hpp"

class Scene
{
private:
    std::vector<Vertex> mVertices;

public:
    Scene();
    ~Scene();
    void Update(Renderer& renderer);

    void SetImGuiContext(struct ImGuiContext* context);
    void ShowImGuiControls();
};
