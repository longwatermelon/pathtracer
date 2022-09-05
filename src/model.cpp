#include "model.h"
#include "util.h"
#include <bits/types/FILE.h>
#include <stdexcept>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>
#include <fmt/format.h>
#include <glm/gtx/intersect.hpp>

Model::Model(glm::vec3 pos, glm::vec3 rot, const std::string &obj, const Material *mat)
    : m_mat(mat)
{
    Assimp::Importer im;
    const aiScene *sc = im.ReadFile(obj, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!sc || sc->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !sc->mRootNode)
    {
        throw std::runtime_error("Assimp error when loading model.");
    }

    process_node(sc->mRootNode, sc);

    move(pos);
    rotate(rot);
}

Model::~Model()
{
}

bool Model::ray_intersect(const Ray &ray, Triangle *tri, glm::vec2 *bary, float *t) const
{
    float nearest = RAY_FARTHEST;

    for (const auto &m : m_meshes)
    {
        float dist;
        glm::vec2 b;
        Triangle tr;
        if (m->ray_intersect(ray, &tr, &b, &dist) && dist < nearest)
        {
            nearest = dist;
            if (bary) *bary = b;
            if (tri) *tri = tr;
        }
    }

    if (t) *t = nearest;
    return nearest < RAY_FARTHEST;
}

void Model::move(glm::vec3 dir)
{
    m_pos += dir;
    for (auto &m : m_meshes)
        m->move(dir);
}

void Model::rotate(glm::vec3 rot)
{
    m_rot += rot;
    for (auto &m : m_meshes)
        m->rotate(rot);
}

void Model::process_node(aiNode *node, const aiScene *sc)
{
    for (size_t i = 0; i < node->mNumMeshes; ++i)
    {
        struct aiMesh *mesh = sc->mMeshes[node->mMeshes[i]];
        m_meshes.emplace_back(process_mesh(mesh, sc));
    }

    for (size_t i = 0; i < node->mNumChildren; ++i)
    {
        process_node(node->mChildren[i], sc);
    }
}

std::unique_ptr<Mesh> Model::process_mesh(aiMesh *mesh, const aiScene *sc)
{
    std::vector<Vertex> verts;
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex v;
        v.pos.x = mesh->mVertices[i].x;
        v.pos.y = mesh->mVertices[i].y;
        v.pos.z = mesh->mVertices[i].z;

        v.norm.x = mesh->mVertices[i].x;
        v.norm.y = mesh->mVertices[i].y;
        v.norm.z = mesh->mVertices[i].z;
        v.norm = glm::normalize(v.norm);

        verts.emplace_back(v);
    }

    for (size_t i = 0; i < mesh->mNumFaces; ++i)
    {
        struct aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; ++j)
            indices.emplace_back(face.mIndices[j]);
    }

    return std::make_unique<Mesh>(verts, indices);
}
