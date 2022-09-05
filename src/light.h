#pragma once
#include <glm/glm.hpp>

struct Light
{
    Light(glm::vec3 pos, glm::vec3 color, float intensity)
        : pos(pos), color(color), in(intensity) {}

    glm::vec3 pos, color;
    float in;
};

struct Material
{
    Material(glm::vec3 col, float shininess)
        : col(col), shininess(shininess) {}

    glm::vec3 col;
    float shininess;
};
