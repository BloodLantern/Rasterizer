#include "camera.hpp"

#include <imgui.h>

Camera::Camera(const unsigned int width, const unsigned int height, Matrix4x4& viewMatrix, Matrix4x4& projectionMatrix)
    : mFramebufferWidth(width),
    mFramebufferHeight(height),
    mView(viewMatrix),
    mProjection(projectionMatrix)
{
}

void Camera::Update()
{
    ImGui::Begin("Camera");
    ImGui::SliderAngle("FOV", &mFOV, -180.f, 180.0f);
    ImGui::SliderFloat("Near", &mNear, 0.1f, 10.0f);
    ImGui::SliderFloat("Far", &mFar, 100.0f, 1000.0f);
    ImGui::SliderFloat3("Up direction", &mUp.x, -10.0f, 10.f, "%.2f");
    ImGui::SliderFloat3("Position", &mPosition.x, -10.0f, 10.f, "%.2f");
    ImGui::SliderFloat3("Looking at", &mLookAt.x, -10.0f, 10.f, "%.2f");
    ImGui::End();
    
    Matrix4x4::ViewMatrix(
        mPosition,
        mLookAt,
        mUp.Normalized(),
        mView
    );

    Matrix4x4::ProjectionMatrix(
        mFOV,
        mFramebufferWidth / (float) mFramebufferHeight,
        mNear,
        mFar,
        mProjection
    );
}
