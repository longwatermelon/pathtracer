#pragma once
#include "light.h"
#include "util.h"
#include <glm/glm.hpp>

class Sphere
{
public:
    Sphere(glm::vec3 c, float r, const Material &mat);
    ~Sphere();

    bool ray_intersect(const Ray &ray, float *t) const;
    bool ray_intersect(const Ray &ray, float *t1, float *t2) const;

    glm::vec3 center() const { return m_center; }
    float radius() const { return m_r; }
    const Material &mat() const { return m_mat; }

private:
    glm::vec3 m_center{ 0.f };
    float m_r{ 0.f };

    Material m_mat;
};
