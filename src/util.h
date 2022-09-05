#pragma once
#include <array>
#include <glm/glm.hpp>

#define RAY_FARTHEST 1000.f

struct Vertex
{
    glm::vec3 pos, norm;
};

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

struct Triangle
{
    Triangle() = default;
    Triangle(Vertex a, Vertex b, Vertex c)
        : verts{ a, b, c } {}

    std::array<Vertex, 3> verts;
};
