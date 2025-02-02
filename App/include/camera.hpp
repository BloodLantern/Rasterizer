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

    float mFOV = (float) -std::numbers::pi / 2;
    Vector3 mUp = Vector3::UnitY();
    Vector3 mPosition = Vector3(10.f, 20.f, -10.f);
    Vector3 mLookAt = Vector3(4.f, 7.f, 0.f);

    Matrix4x4& mView;
    Matrix4x4& mProjection;
};
