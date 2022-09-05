#pragma once
#include "sphere.h"
#include "light.h"
#include "model.h"
#include <vector>

class Scene
{
public:
    Scene();
    ~Scene();

    void add_sphere(const Sphere &s);
    void add_model(Model m);
    void add_light(const Light &l);

    // Cast ray considering all objects in scene
    bool cast_ray(glm::vec3 orig, glm::vec3 dir, glm::vec3 *hit, glm::vec3 *norm, const Material **mat);

    const std::vector<Light> &lights() const { return m_lights; }
    float floor_y() const { return m_floor_y; }

private:
    std::vector<Sphere> m_spheres;
    std::vector<Model> m_models;
    std::vector<Light> m_lights;

    float m_floor_y{ 3.f };
    Material m_floor_mat;
};
