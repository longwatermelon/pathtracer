#include "scene.h"
#include <glm/glm.hpp>

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::add_sphere(const Sphere &s)
{
    m_spheres.emplace_back(s);
}

void Scene::add_light(const Light &l)
{
    m_lights.emplace_back(l);
}

bool Scene::cast_ray_spheres(glm::vec3 orig, glm::vec3 dir, glm::vec3 *hit, glm::vec3 *norm, const Material **mat)
{
    float nearest = 1000.f;

    for (auto &s : m_spheres)
    {
        float t;

        if (s.ray_intersect(orig, dir, &t) && t < nearest)
        {
            nearest = t;
            if (hit) *hit = orig + dir * t;
            if (norm) *norm = glm::normalize(*hit - s.center());
            if (mat) *mat = &s.mat();
        }
    }

    return nearest < 1000.f;
}
