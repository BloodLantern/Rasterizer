#include "scene.hpp"

Scene::Scene()
{
    m_Vertices.clear();

    m_Vertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)));
    m_Vertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)));
    m_Vertices.push_back(Vertex(Vector3(0.0f, 0.5f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)));
}

Scene::~Scene()
{
}

void Scene::Update(const float deltaTime, Renderer& renderer)
{
    // renderer.DrawTriangles(m_Vertices.data(), m_Vertices.size());
}

void Scene::SetImGuiContext(struct ImGuiContext* context)
{
}

void Scene::ShowImGuiControls()
{
}
