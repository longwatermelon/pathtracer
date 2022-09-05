#pragma once
#include "scene.h"
#include "util.h"
#include <string>

struct RayIntersection
{
    Ray ray;
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
    glm::vec3 cast_ray(const Ray &ray);

    void write(const std::vector<glm::vec3> &frame, const std::string &out);

    glm::vec3 phong(const RayIntersection &data);
    glm::vec3 volumetric(const Ray &ray);

private:
    int m_w{ 1000 }, m_h{ 1000 };
    Scene m_sc;

    Material m_mesh_mat;
};
