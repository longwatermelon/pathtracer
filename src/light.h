#pragma once
#include <glm/glm.hpp>

struct Light
{
    Light(glm::vec3 pos, glm::vec3 color, float ambient, float diffuse, float specular)
        : pos(pos), color(color), ambient(ambient), diffuse(diffuse), specular(specular) {}

    glm::vec3 pos;
    glm::vec3 color;
    float ambient, diffuse, specular;
};

struct Material
{
    Material(glm::vec3 col, float shininess)
        : col(col), shininess(shininess) {}

    glm::vec3 col;
    float shininess;
};
