#pragma once

#include <vector2.hpp>
#include <vector3.hpp>
#include <vector4.hpp>

class Vertex
{
public:
    Vector3 Position;
    Vector4 Color;
    Vector3 Normal;
    Vector2 UVs;

    Vertex(const Vector3& position);
    Vertex(const Vector3& position, const Vector4& color);
    Vertex(const Vector3& position, const Vector4& color, const Vector3& normal, const Vector2 uv);

    void SetPosition(const Vector3& position);
    void SetColor(const Vector4& color);
    void SetNormal(const Vector3& normal);
    void SetUV(const Vector2 uv);

    void SetPositionAndNormal(const Vector3& position);
};
