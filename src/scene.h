#pragma once
#include "sphere.h"
#include <vector>

class Scene
{
public:
    Scene();
    ~Scene();

    void add_sphere(const Sphere &s);

    bool cast_ray_spheres(glm::vec3 orig, glm::vec3 dir, glm::vec3 *hit, glm::vec3 *norm, const Sphere *s);

private:
    std::vector<Sphere> m_spheres;
};
