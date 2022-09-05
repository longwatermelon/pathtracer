#include "scene.h"
#include "util.h"
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

void Scene::add_model(Model m)
{
    m_models.emplace_back(std::move(m));
}

void Scene::add_light(const Light &l)
{
    m_lights.emplace_back(l);
}

bool Scene::cast_ray(const Ray &ray, glm::vec3 *hit, glm::vec3 *norm, const Material **mat)
{
    float nearest = RAY_FARTHEST;

    for (auto &s : m_spheres)
    {
        float t;

        if (s.ray_intersect(ray, &t) && t < nearest)
        {
            nearest = t;
            if (hit) *hit = ray.forward(t);
            if (norm) *norm = glm::normalize(*hit - s.center());
            if (mat) *mat = &s.mat();
        }
    }

    for (const auto &m : m_models)
    {
        float t;
        glm::vec2 bary;
        Triangle tri;

        if (m.ray_intersect(ray, &tri, &bary, &t) && t < nearest)
        {
            nearest = t;
            if (hit) *hit = ray.forward(t);
            if (mat) *mat = m.mat();
            if (norm) *norm = (1 - bary[0] - bary[1]) * tri.verts[0].norm + bary[0] * tri.verts[1].norm + bary[1] * tri.verts[2].norm;
            // if (norm) *norm = tri.verts[1].norm;
        }
    }

    // In case no sphere is intersected
    glm::vec3 end = ray.forward(nearest);

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

    return nearest < RAY_FARTHEST;
}
