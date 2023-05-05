#pragma once

#include <vector>

#include "vertex.hpp"
#include "renderer.hpp"

class Scene
{
private:
    std::vector<Vertex> m_Vertices;

public:
    Scene();
    ~Scene();
    void Update(const float deltaTime, Renderer& renderer);

    void SetImGuiContext(struct ImGuiContext* context);
    void ShowImGuiControls();
};
