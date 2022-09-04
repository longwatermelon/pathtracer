#pragma once
#include <glm/glm.hpp>

class Sphere
{
public:
    Sphere(glm::vec3 c, float r);
    ~Sphere();

    bool ray_intersect(glm::vec3 orig, glm::vec3 dir, float *t) const;

    glm::vec3 center() const { return m_center; }
    float radius() const { return m_r; }

private:
    glm::vec3 m_center{ 0.f };
    float m_r{ 0.f };
};
