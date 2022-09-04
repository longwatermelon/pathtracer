#include "render.h"
#include <fstream>
#include <vector>
#include <fmt/format.h>
#include <glm/glm.hpp>

Renderer::Renderer(int w, int h)
    : m_w(w), m_h(h)
{
}

Renderer::~Renderer()
{
}

void Renderer::render(const std::string &out)
{
    std::vector<glm::vec3> frame(m_w * m_h);

    for (int i = 0; i < m_w * m_h; ++i)
    {
        frame[i] = glm::vec3(1.f, 0.f, 0.f);
    }

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
