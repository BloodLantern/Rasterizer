#include "model.hpp"

#include <tiny_obj_loader.h>

Model::Model(const char *const filepath)
{
    Load(filepath);
}

void Model::Load(const char *const filepath)
{
    mVertices.clear();
    
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath))
        throw std::runtime_error(warn + err);

    for (const tinyobj::shape_t& shape : shapes)
        for (const tinyobj::index_t& index : shape.mesh.indices)
        {
            Vertex v(
                Vector3(
                    attrib.vertices[3 * index.vertex_index],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
                ),
                1,
                Vector3(
                    attrib.normals[3 * index.normal_index],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                ),
                Vector2(
                    attrib.texcoords[2 * index.texcoord_index],
                    attrib.texcoords[2 * index.texcoord_index + 1]
                )
            );

            mVertices.push_back(v);
        }
}
