#include "scene.hpp"

#include <imgui.h>

Scene::Scene()
    : mTexture(mTexturePath.data()),
    mModelTexture(mModelTexturePath.data()),
    mModel(mModelPath.data())
{
    // Triangle vertices
    mVertices.push_back(Vertex(Vector3(-10.f, -10.f, 0.f), Vector4(1.f, 1.f, 1.f, 1.f),
        Vector3(0.f, 0.f, 0.f), Vector2(0.f, 0.f)));
    mVertices.push_back(Vertex(Vector3(10.f, -10.f, 0.f), Vector4(1.f, 1.f, 1.f, 1.f),
        Vector3(0.f, 0.f, 0.f), Vector2(1.f, 0.f)));
    mVertices.push_back(Vertex(Vector3(0.f, 10.f, 0.f), Vector4(1.f, 1.f, 1.f, 1.f),
        Vector3(0.f, 0.f, 0.f), Vector2(0.5f, 1.f)));
}

bool showTriangle = false;

void Scene::Update(Renderer& renderer)
{
    renderer.ModelMatrix = Matrix4x4::TRS(mWorldPosition, mWorldRotation, mWorldScale);

    if (showTriangle)
        renderer.Render(mVertices, mTexture);
    else
        renderer.Render(mModel.GetVertices(), mModelTexture);
}

void Scene::ShowImGuiControls()
{
    ImGui::Begin("Controls");
    ImGui::Text("%f FPS", 1.f / ImGui::GetIO().DeltaTime);
    ImGui::Checkbox("Show Triangle", &showTriangle);
    ImGui::InputText("Triangle texture file path", mTexturePath.data(), mTexturePath.size());
    if (ImGui::Button("Load triangle texture"))
        mTexture.Load(mTexturePath.data());
    ImGui::InputText("3D model texture file path", mModelTexturePath.data(), mModelTexturePath.size());
    if (ImGui::Button("Load 3D model texture"))
        mModel.Load(mModelTexturePath.data());
    ImGui::InputText("3D model file path", mModelPath.data(), mModelPath.size());
    if (ImGui::Button("Load 3D model"))
        mModelTexture.Load(mModelTexturePath.data());
    ImGui::End();

    ImGui::Begin("World transformations");
    ImGui::SliderFloat3("Position", &mWorldPosition.x, -20.f, 20.f);
    ImGui::SliderAngle("Rotation X", &mWorldRotation.x, -180.f, 180.f);
    ImGui::SliderAngle("Rotation Y", &mWorldRotation.y, -180.f, 180.f);
    ImGui::SliderAngle("Rotation Z", &mWorldRotation.z, -180.f, 180.f);
    ImGui::SliderFloat3("Scale", &mWorldScale.x, -10.f, 10.f);
    ImGui::End();
}
