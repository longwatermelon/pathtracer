#pragma once
#include "util.h"
#include <vector>
#include <glm/glm.hpp>

class Mesh
{
public:
    Mesh(const std::vector<Vertex> &verts, const std::vector<unsigned int> &indices);
    ~Mesh();

    bool ray_intersect(const Ray &ray, Triangle *tri, glm::vec2 *bary, float *t) const;

    void move(glm::vec3 dir);
    void rotate(glm::vec3 rot);

private:
    glm::vec3 m_pos{ 0.f }, m_rot{ 0.f };

    std::vector<Vertex> m_verts;
    std::vector<unsigned int> m_indices;
};
