#pragma once

#include <vector2i.hpp>
#include <vector4.hpp>

class Texture
{
public:
    Texture(const char* const filepath);
    ~Texture();

    void Load(const char* const filepath);
    Vector4& Sample(const Vector2 uv) const;

private:
    Vector2i mSize;
    Vector4* mPixels;
    unsigned char* mStbImageData = nullptr;
};
