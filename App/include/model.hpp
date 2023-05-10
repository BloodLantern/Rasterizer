#pragma once

#include <vector>

#include "vertex.hpp"

class Model
{
public:
    Model(const char* const filepath);

    void Load(const char* const filepath);
    const std::vector<Vertex>& GetVertices() const { return mVertices; }

private:
    std::vector<Vertex> mVertices;
};
