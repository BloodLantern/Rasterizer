#include "scene.hpp"

Scene::Scene()
{
    mVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.f), Vector4(1.f, 0.f, 0.f, 1.f),
        Vector3(0.f, 0.f, 0.f), Vector2(0.f, 0.f)));
    mVertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.f), Vector4(0.f, 1.f, 0.f, 1.f),
        Vector3(0.f, 0.f, 0.f), Vector2(1.f, 0.f)));
    mVertices.push_back(Vertex(Vector3(0.f, 0.5f, 0.f), Vector4(0.f, 0.f, 1.f, 1.f),
        Vector3(0.f, 0.f, 0.f), Vector2(0.5f, 1.f)));
}

Scene::~Scene()
{
}

void Scene::Update(Renderer& renderer)
{
    renderer.Render(mVertices);
}

void Scene::SetImGuiContext(struct ImGuiContext* context)
{
}

void Scene::ShowImGuiControls()
{
}
