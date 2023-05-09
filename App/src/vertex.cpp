#include "vertex.hpp"

Vertex::Vertex(const Vector3& position)
	: Position(position)
{
}

Vertex::Vertex(const Vector3& position, const Vector4& color)
	: Position(position), Color(color)
{
}

Vertex::Vertex(const Vector3& position, const Vector4& color, const Vector3& normal, const Vector2 uv)
	: Position(position), Color(color), Normal(normal), UVs(uv)
{
}

void Vertex::SetPosition(const Vector3& position)
{
	Position = position;
}

void Vertex::SetColor(const Vector4& color)
{
	Color = color;
}

void Vertex::SetNormal(const Vector3& normal)
{
	Normal = normal;
}

void Vertex::SetUV(const Vector2 uv)
{
	UVs = uv;
}

void Vertex::SetPositionAndNormal(const Vector3& position)
{
	Position = position;
	Normal = position.Normalized();
}
