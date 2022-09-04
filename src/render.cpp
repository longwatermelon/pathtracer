#include "render.h"
#include <fstream>
#include <vector>
#include <fmt/format.h>
#include <glm/glm.hpp>

Renderer::Renderer(int w, int h)
    : m_w(w), m_h(h)
{
    m_sc.add_sphere(Sphere(glm::vec3(5.f, 0.f, 0.f), 1.f));
}

Renderer::~Renderer()
{
}

void Renderer::render(const std::string &out)
{
    std::vector<glm::vec3> frame(m_w * m_h);
    cast_rays(frame);

    std::ofstream ofs(out);
    ofs << fmt::format("P3\n{} {}\n255\n", m_w, m_h);

    for (int i = 0; i < m_w * m_h; ++i)
    {
        int r = std::max(std::min(frame[i].x, 1.f), 0.f) * 255.f;
        int g = std::max(std::min(frame[i].y, 1.f), 0.f) * 255.f;
        int b = std::max(std::min(frame[i].z, 1.f), 0.f) * 255.f;

        ofs << fmt::format("{} {} {}\n", r, g, b);
    }

    ofs.close();
}

void Renderer::cast_rays(std::vector<glm::vec3> &frame)
{
    float fov = 1.f;

    for (int y = 0; y < m_h; ++y)
    {
        for (int z = 0; z < m_w; ++z)
        {
            float ha = ((float)z / m_w) * fov - (fov / 2.f);
            float va = ((float)y / m_h) * fov - (fov / 2.f);

            glm::vec3 dir = glm::normalize(glm::vec3(1.f, va, ha));
            frame[y * m_w + z] = cast_ray(glm::vec3(0.f, 0.f, 0.f), dir);
        }
    }
}

glm::vec3 Renderer::cast_ray(glm::vec3 orig, glm::vec3 dir)
{
    glm::vec3 hit, norm;
    const Sphere *s;

    if (!m_sc.cast_ray_spheres(orig, dir, &hit, &norm, s))
        return glm::vec3(0.f, 0.f, 0.f);

    return glm::vec3(1.f, 0.f, 0.f);
}