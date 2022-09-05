#include "mesh.h"

Mesh::Mesh(const std::vector<Vertex> &verts, const std::vector<unsigned int> &indices)
    : m_verts(verts), m_indices(indices)
{
}

Mesh::~Mesh()
{
}
