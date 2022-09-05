#include "scene.h"
#include <iostream>
#include <glm/glm.hpp>

Scene::Scene()
    : m_floor_mat(glm::vec3(0.f, 1.f, .3f), 20.f)
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

bool Scene::cast_ray(glm::vec3 orig, glm::vec3 dir, glm::vec3 *hit, glm::vec3 *norm, const Material **mat)
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

    // In case no sphere is intersected
    glm::vec3 end = orig + nearest * dir;

    if (end.y >= m_floor_y)
    {
        if (mat) *mat = &m_floor_mat;
        if (norm) *norm = glm::vec3(0.f, -1.f, 0.f);

        if (hit)
        {
            hit->y = m_floor_y;
            hit->x = end.x / end.y * m_floor_y;
            hit->z = end.z / end.y * m_floor_y;
        }

        return true;
    }

    return nearest < 1000.f;
}
