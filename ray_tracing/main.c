#include "camera.h"
#include "sphere.h"
#include "vec3.h"

#include <math.h>
#include <stdlib.h>

int main(void)
{
    // World
    sphere_list *world = malloc(sizeof *world);
    sphere_list_add(world, init_sphere(init_p3(0.0, -100.5, -1.0), 100));
    sphere_list_add(world, init_sphere(init_p3(0.0, 0.0, -1.0), 0.5));

    render(world);

    return 0;
}