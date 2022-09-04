#pragma once
#include "sphere.h"
#include "light.h"
#include <vector>

class Scene
{
public:
    Scene();
    ~Scene();

    void add_sphere(const Sphere &s);
    void add_light(const Light &l);

    bool cast_ray_spheres(glm::vec3 orig, glm::vec3 dir, glm::vec3 *hit, glm::vec3 *norm, const Material **mat);

    const std::vector<Light> &lights() const { return m_lights; }

private:
    std::vector<Sphere> m_spheres;
    std::vector<Light> m_lights;

    float m_floor_y{ 2.f };
};
