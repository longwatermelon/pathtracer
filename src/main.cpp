#include "render.h"
#include <iostream>

int main(int argc, char **argv)
{
    Renderer r(1000, 1000);
    r.render("out.ppm");

    return 0;
}
