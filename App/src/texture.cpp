#include "texture.hpp"

#include <stb_image.h>

#include <iostream>

Texture::Texture(const char *const filepath)
{
    int nbrChannels;
    unsigned char* result = stbi_load(filepath, &mSize.x, &mSize.y, &nbrChannels, 0);

    mPixels = new Vector4[mSize.x * mSize.y];

    for (int y = 0; y < mSize.y; y++)
        for (int x = 0; x < mSize.x; x++)
        {
            const int texOffset = (x + y * mSize.x) * 3;
            mPixels[x + y * mSize.x] = Vector4(
                result[texOffset],
                result[texOffset + 1],
                result[texOffset + 2],
                255.f
            ) / 255.f;
        }
}

Texture::~Texture()
{
    delete[] mPixels;
}

Vector4& Texture::Sample(const Vector2 uv) const
{
    const int x = (int) std::floor(uv.x * mSize.x);
    const int y = (int) std::floor(uv.y * mSize.y);

    return mPixels[x + y * mSize.x];
}
