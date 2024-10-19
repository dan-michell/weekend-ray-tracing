#include "ray.h"

#include "vec3.h"

void init_ray(ray *r, point3 origin, vec3 direction)
{
    r->origin = origin;
    r->direction = direction;
}

point3 ray_origin(ray r) { return r.origin; }

vec3 ray_direction(ray r) { return r.direction; }

point3 ray_interpolate(ray r, double t) { return v3_add(r.origin, v3_scale(r.direction, t)); }
