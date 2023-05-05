#include "scene.hpp"

Scene::Scene()
{
    mVertices.clear();

    mVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)));
    mVertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)));
    mVertices.push_back(Vertex(Vector3(0.0f, 0.5f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)));
}

Scene::~Scene()
{
}

void Scene::Update(const float deltaTime, Renderer& renderer)
{
    renderer.DrawTriangles(mVertices.data(), mVertices.size());
}

void Scene::SetImGuiContext(struct ImGuiContext* context)
{
}

void Scene::ShowImGuiControls()
{
}
