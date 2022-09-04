#pragma once
#include <glm/glm.hpp>

struct Light
{
    Light(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
        : pos(pos), ambient(ambient), diffuse(diffuse), specular(specular) {}

    glm::vec3 pos;
    glm::vec3 ambient, diffuse, specular;
};

struct Material
{
    Material(glm::vec3 col, float shininess)
        : col(col), shininess(shininess) {}

    glm::vec3 col;
    float shininess;
};
