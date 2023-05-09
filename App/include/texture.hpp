#pragma once

#include <vector2i.hpp>
#include <vector4.hpp>

class Texture
{
public:
    Texture(const char* const filepath);
    ~Texture();

    Vector4& Sample(const Vector2 uv) const;

private:
    Vector2i mSize;
    Vector4* mPixels;
};
