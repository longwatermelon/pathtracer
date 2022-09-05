#pragma once
#include "mesh.h"
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <assimp/scene.h>

class Model
{
public:
    Model(glm::vec3 pos, glm::vec3 rot, const std::string &obj);
    Model(Model&&) = default;
    ~Model();

    void process_node(aiNode *node, const aiScene *sc);
    std::unique_ptr<Mesh> process_mesh(aiMesh *mesh, const aiScene *sc);

private:
    glm::vec3 m_pos{ 0.f }, m_rot{ 0.f };

    std::vector<std::unique_ptr<Mesh>> m_meshes;
};
