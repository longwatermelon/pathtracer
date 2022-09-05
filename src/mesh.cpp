#include "mesh.h"
#include "util.h"
#include <array>
#include <glm/geometric.hpp>
#include <glm/gtx/intersect.hpp>

Mesh::Mesh(const std::vector<Vertex> &verts, const std::vector<unsigned int> &indices)
    : m_verts(verts), m_indices(indices)
{
}

Mesh::~Mesh()
{
}

bool Mesh::ray_intersect(const Ray &ray, Triangle *tri, glm::vec2 *bary, float *t) const
{
    float nearest = RAY_FARTHEST;

    for (size_t i = 0; i < m_indices.size(); i += 3)
    {
        std::array<Vertex, 3> verts = {
            m_verts[m_indices[i]],
            m_verts[m_indices[i + 1]],
            m_verts[m_indices[i + 2]]
        };

        // if (glm::cross(verts[2].pos - verts[0].pos, verts[1].pos - verts[0].pos).x < 0.f)
        //     continue;

        verts[0].pos += m_pos;
        verts[1].pos += m_pos;
        verts[2].pos += m_pos;

        glm::vec2 b;
        float dist;
        if (glm::intersectRayTriangle(ray.orig, ray.dir, verts[0].pos, verts[1].pos, verts[2].pos, b, dist))
        {
            if (dist < nearest)
            {
                nearest = dist;
                if (bary) *bary = b;
                if (tri) *tri = Triangle(verts[0], verts[1], verts[2]);
            }
        }
    }

    if (t) *t = nearest;
    return nearest < RAY_FARTHEST && nearest > 0.f;
}

void Mesh::move(glm::vec3 dir)
{
    m_pos += dir;
}

void Mesh::rotate(glm::vec3 rot)
{
    m_rot += rot;
}
