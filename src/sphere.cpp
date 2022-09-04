#include "sphere.h"
#include <glm/glm.hpp>

Sphere::Sphere(glm::vec3 c, float r)
    : m_center(c), m_r(r)
{
}

Sphere::~Sphere()
{
}

bool Sphere::ray_intersect(glm::vec3 orig, glm::vec3 dir, float *t) const
{
    glm::vec3 co = orig - m_center;
    float a = glm::dot(dir, dir);
    float b = glm::dot(co, dir) * 2.f;
    float c = glm::dot(co, co) - m_r * m_r;

    float discrim = b * b - 4.f * a * c;
    if (discrim < 0.f) return false;

    float t1 = (-b + std::sqrt(discrim)) / (2.f * a);
    float t2 = (-b - std::sqrt(discrim)) / (2.f * a);

    if (t1 <= 1e-4f) return false;

    if (t2 <= 1e-4f) *t = t1;
    else *t = (t1 < t2 ? t1 : t2);

    return true;
}
