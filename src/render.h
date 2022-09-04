#pragma once
#include <string>

class Renderer
{
public:
    Renderer(int w, int h);
    ~Renderer();

    void render(const std::string &out);

private:
    int m_w, m_h;
};
