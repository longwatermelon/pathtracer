#pragma once
#include <glm/glm.hpp>

struct Ray
{
    Ray() = default;
    Ray(glm::vec3 orig, glm::vec3 dir)
        : orig(orig), dir(dir) {}

    glm::vec3 forward(float t) const
    {
        return orig + dir * t;
    }

    glm::vec3 orig{ 0.f }, dir{ 0.f };
};
