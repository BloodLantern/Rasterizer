#include "scene.hpp"

#include <imgui.h>

Scene::Scene()
    : mTexture("assets/texture.jpeg"),
    mModelTexture("assets/model_texture.jpg"),
    mModel("assets/model.obj")
{
    // Triangle vertices
    mVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.f), Vector4(1.f, 0.f, 0.f, 1.f),
        Vector3(0.f, 0.f, 0.f), Vector2(0.f, 0.f)));
    mVertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.f), Vector4(0.f, 1.f, 0.f, 1.f),
        Vector3(0.f, 0.f, 0.f), Vector2(1.f, 0.f)));
    mVertices.push_back(Vertex(Vector3(0.f, 0.5f, 0.f), Vector4(0.f, 0.f, 1.f, 1.f),
        Vector3(0.f, 0.f, 0.f), Vector2(0.5f, 1.f)));
}

bool showTriangle = false;

void Scene::Update(Renderer& renderer)
{
    if (showTriangle)
        renderer.Render(mVertices, mTexture);
    else
        renderer.Render(mModel.GetVertices(), mModelTexture);
}

void Scene::ShowImGuiControls()
{
    ImGui::Begin("Controls");
    ImGui::Checkbox("Show Triangle", &showTriangle);
    ImGui::End();
}
