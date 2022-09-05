#pragma once
#include "scene.h"
#include <string>

struct RayIntersection
{
    glm::vec3 orig, dir;
    glm::vec3 hit, norm;

    const Material *mat;
};

class Renderer
{
public:
    Renderer(int w, int h);
    ~Renderer();

    void render(const std::string &out);

    void cast_rays(std::vector<glm::vec3> &frame);
    glm::vec3 cast_ray(glm::vec3 orig, glm::vec3 dir);

    glm::vec3 phong(const RayIntersection &data);
    glm::vec3 volumetric(glm::vec3 orig, glm::vec3 dir);

private:
    int m_w{ 1000 }, m_h{ 1000 };
    Scene m_sc;

    Material m_mesh_mat;
};
