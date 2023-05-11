#include "scene.hpp"

#include <imgui.h>

Scene::Scene()
    : mTexture(mTexturePath),
    mMountainModelTexture(mMountainModelTexturePath),
    mMountainModel(mMountainModelPath),
    mModelTexture(mModelTexturePath),
    mModel(mModelPath)
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
    {
        renderer.Render(mMountainModel.GetVertices(), mMountainModelTexture);
    }
}

void Scene::ShowImGuiControls()
{
    ImGui::Begin("Controls");
    ImGui::Text("%f FPS", 1.f / ImGui::GetIO().DeltaTime);
    ImGui::Checkbox("Show Triangle", &showTriangle);
    ImGui::InputText("Triangle texture file path", mTexturePath, MaxFilepathLength);
    if (ImGui::Button("Load triangle texture"))
        mTexture.Load(mTexturePath);
    ImGui::InputText("3D model 1 texture file path", mMountainModelTexturePath, MaxFilepathLength);
    if (ImGui::Button("Load 3D model 1 texture"))
        mMountainModelTexture.Load(mMountainModelTexturePath);
    ImGui::InputText("3D model 1 file path", mMountainModelPath, MaxFilepathLength);
    if (ImGui::Button("Load 3D model 1"))
        mMountainModel.Load(mMountainModelPath);
    ImGui::InputText("3D model 2 texture file path", mMountainModelTexturePath, MaxFilepathLength);
    if (ImGui::Button("Load 3D model 2 texture"))
        mModelTexture.Load(mModelTexturePath);
    ImGui::InputText("3D model 2 file path", mModelPath, MaxFilepathLength);
    if (ImGui::Button("Load 3D model 2"))
        mModel.Load(mModelPath);
    ImGui::End();

    ImGui::Begin("World transformations");
    ImGui::SliderFloat3("Position", &mWorldPosition.x, -20.f, 20.f);
    ImGui::SliderAngle("Rotation X", &mWorldRotation.x);
    ImGui::SliderAngle("Rotation Y", &mWorldRotation.y);
    ImGui::SliderAngle("Rotation Z", &mWorldRotation.z);
    ImGui::SliderFloat3("Scale", &mWorldScale.x, -10.f, 10.f);
    ImGui::End();
}
