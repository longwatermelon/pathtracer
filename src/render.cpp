#include "render.h"
#include "light.h"
#include "model.h"
#include <cstdio>
#include <fstream>
#include <glm/exponential.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <vector>
#include <fmt/format.h>
#include <glm/glm.hpp>

Renderer::Renderer(int w, int h)
    : m_w(w), m_h(h), m_mesh_mat(glm::vec3(0.f, 0.f, 1.f), 50.f)
{
    Material mat(glm::vec3(1.f, 0.f, 0.f), 50.f);
    // m_sc.add_sphere(Sphere(glm::vec3(10.f, 0.f, 0.f), 1.f, mat));
    m_sc.add_model(Model(glm::vec3(10.f, 0.f, 0.f), glm::vec3(0.f), "res/cube.obj", &m_mesh_mat));

    m_sc.add_light(Light(glm::vec3(8.f, -4.f, 2.f), glm::vec3(1.f, 1.f, .7f), 1.f));
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
            frame[y * m_w + z] = cast_ray(Ray(glm::vec3(0.f, 0.f, 0.f), dir));
        }

        if (y % 100 == 0)
        {
            fmt::print("\rFinished {}/{} rows", y, m_h);
            std::fflush(stdout);
        }
    }
}

glm::vec3 Renderer::cast_ray(const Ray &ray)
{
    RayIntersection data;
    data.ray = ray;

    if (!m_sc.cast_ray(ray, &data.hit, &data.norm, &data.mat))
        return volumetric(ray);

    return phong(data) + volumetric(ray);
}

glm::vec3 Renderer::phong(const RayIntersection &data)
{
    glm::vec3 res(0.f);

    float l_ambient = .2f;
    float l_diffuse = .5f;
    float l_specular = .8f;

    for (const auto &light : m_sc.lights())
    {
        // ambient
        res += light.color * light.in * l_ambient * data.mat->col;

        // shadows (If shadow, only show ambient)
        glm::vec3 shadow_orig = data.hit + data.norm / 1e3f;
        glm::vec3 shadow_dir = glm::normalize(light.pos - shadow_orig);

        glm::vec3 shadow_hit;
        if (m_sc.cast_ray(Ray(shadow_orig, shadow_dir), &shadow_hit, 0, 0))
        {
            if (glm::distance(shadow_hit, shadow_orig) < glm::distance(light.pos, shadow_orig))
                continue;
        }

        // diffuse
        glm::vec3 ldir = glm::normalize(light.pos - data.hit);
        float diff = std::max(glm::dot(data.norm, ldir), 0.f);
        glm::vec3 diffuse = light.color * light.in * l_diffuse * diff * data.mat->col;

        // specular
        glm::vec3 vdir = glm::normalize(data.ray.orig - data.hit);
        glm::vec3 refdir = glm::reflect(-ldir, data.norm);
        float spec = std::pow(std::max(glm::dot(vdir, refdir), 0.f), data.mat->shininess);
        glm::vec3 specular = light.color * light.in * l_specular * spec * data.mat->col;

        res += diffuse + specular;
    }

    return res;
}

glm::vec3 Renderer::volumetric(const Ray &ray)
{
    glm::vec3 res(0.f);

    glm::vec3 pos = ray.orig;
    for (size_t i = 0; i < 300; ++i)
    {
        pos += ray.dir / 15.f;
        if (pos.y >= m_sc.floor_y())
            break;

        for (const auto &light : m_sc.lights())
        {
            float dist = glm::distance(light.pos, pos);
            float attn = 1.f / (dist * dist);

            // Detect if under shadow
            glm::vec3 shadow_dir = glm::normalize(light.pos - pos);
            if (!m_sc.cast_ray(Ray(pos, shadow_dir), 0, 0, 0))
                res += light.in * (light.color / 40.f * attn);
            else
                res -= light.color / 1000.f;
        }
    }

    return res;
}
