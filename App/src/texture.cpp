#include "texture.hpp"

#include <stb_image.h>

#include <iostream>

Texture::Texture(const char *const filepath)
{
    Load(filepath);
}

Texture::~Texture()
{
    if (mStbImageData)
        stbi_image_free(mStbImageData);
    delete[] mPixels;
}

void Texture::Load(const char *const filepath)
{
    int nbrChannels;
    unsigned char* data = stbi_load(filepath, &mSize.x, &mSize.y, &nbrChannels, 0);
    if (data)
    {
        if (mStbImageData)
            stbi_image_free(mStbImageData);
        delete[] mPixels;
        mPixels = nullptr;

        mStbImageData = data;
    }
    else
    {
        std::cerr << "Failed to load texture: " << filepath << std::endl;
        return;
    }

    mPixels = new Vector4[mSize.x * mSize.y];

    for (int y = 0; y < mSize.y; y++)
        for (int x = 0; x < mSize.x; x++)
        {
            const int texOffset = (x + y * mSize.x) * nbrChannels;
            mPixels[x + y * mSize.x] = Vector4(
                mStbImageData[texOffset],
                mStbImageData[texOffset + 1],
                mStbImageData[texOffset + 2],
                nbrChannels == 4 ? mStbImageData[texOffset + 3] : 255.f
            ) / 255.f;
        }
        
    std::cout << "Successfully loaded texture: " << filepath << std::endl;
}

Vector4 &Texture::Sample(const Vector2 uv) const
{
    const int x = (int) std::floor(uv.x * mSize.x);
    const int y = (int) std::floor(uv.y * mSize.y);

    return mPixels[x + y * mSize.x];
}
