#include "vertex.hpp"

Vertex::Vertex(const Vector3& position)
	: mPosition(position)
{
}

Vertex::Vertex(const Vector3& position, const Vector4& color)
	: mPosition(position), mColor(color)
{
}

Vertex::Vertex(const Vector3& position, const Vector4& color, const Vector3& normal, const Vector2 uv)
	: mPosition(position), mColor(color), mNormal(normal), mUVs(uv)
{
}

void Vertex::SetPosition(const Vector3& position)
{
	mPosition = position;
}

void Vertex::SetColor(const Vector4& color)
{
	mColor = color;
}

void Vertex::SetNormal(const Vector3& normal)
{
	mNormal = normal;
}

void Vertex::SetUV(const Vector2 uv)
{
	mUVs = uv;
}

void Vertex::SetPositionAndNormal(const Vector3& position)
{
	mPosition = position;
	mNormal = position.Normalized();
}
