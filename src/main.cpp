#include "render.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
    Renderer r(300, 300);
    r.render("out.ppm");

    std::system("feh out.ppm");

    return 0;
}
