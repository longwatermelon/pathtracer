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

bool Scene::cast_ray_spheres(glm::vec3 orig, glm::vec3 dir, glm::vec3 *hit, glm::vec3 *norm, const Sphere *s)
{
    float nearest = 1000.f;

    for (const auto &s : m_spheres)
    {
        float t;

        if (s.ray_intersect(orig, dir, &t) && t < nearest)
        {
            nearest = t;
            if (hit) *hit = orig + dir * t;
            if (norm) *norm = glm::normalize(*hit - s.center());
        }
    }

    return nearest < 1000.f;
}
