#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef vec3 point3;

typedef struct
{
    point3 origin;
    vec3 direction;
} ray;

void init_point3(point3 *p, float x, float y, float z);
void init_ray(ray *r, point3 origin, vec3 direction);
point3 ray_interpolate(ray r, double t);

#endif