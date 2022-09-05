#pragma once
#include "mesh.h"
#include "light.h"
#include "util.h"
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <assimp/scene.h>

class Model
{
public:
    Model(glm::vec3 pos, glm::vec3 rot, const std::string &obj, const Material *mat);
    Model(Model&&) = default;
    ~Model();

    bool ray_intersect(const Ray &ray, Triangle *tri, glm::vec2 *bary, float *t) const;

    void move(glm::vec3 dir);
    void rotate(glm::vec3 rot);

    void process_node(aiNode *node, const aiScene *sc);
    std::unique_ptr<Mesh> process_mesh(aiMesh *mesh, const aiScene *sc);

    const Material *mat() const { return m_mat; }

private:
    glm::vec3 m_pos{ 0.f }, m_rot{ 0.f };

    std::vector<std::unique_ptr<Mesh>> m_meshes;
    const Material *m_mat = nullptr;
};
