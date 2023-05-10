#pragma once

#include <matrix4x4.hpp>
#include <vector3.hpp>

#include <numbers>

class Camera
{
public:
    Camera(const unsigned int width, const unsigned int height, Matrix4x4& viewMatrix, Matrix4x4& projectionMatrix);

    void Update();

private:
    const unsigned int mFramebufferWidth;
    const unsigned int mFramebufferHeight;

    float mNear = 0.1f;
    float mFar = 100.f;

    float mFOV = (float) std::numbers::pi / 2;
    Vector3 mUp = Vector3::UnitY();
    Vector3 mPosition = Vector3(0.f, 1.7f, 0.9f);
    Vector3 mLookAt = Vector3(0.f, -1.5f, 0.f);

    Matrix4x4& mView;
    Matrix4x4& mProjection;
};
