#pragma once
#include <vector>
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 pos, norm;
};

class Mesh
{
public:
    Mesh(const std::vector<Vertex> &verts, const std::vector<unsigned int> &indices);
    ~Mesh();

private:
    glm::vec3 m_pos{ 0.f }, m_rot{ 0.f };

    std::vector<Vertex> m_verts;
    std::vector<unsigned int> m_indices;
};
