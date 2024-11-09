#ifndef CAMERA_H
#define CAMERA_H

#include "colour.h"
#include "sphere.h"
#include "ray.h"

typedef struct
{
    float aspect_ratio, focal_length, pixel_samples_scale;
    int image_width, image_height, samples_per_pixel;
    point3 camera_centre, pixel_upper_left;
    vec3 pixel_delta_u, pixel_delta_v;
} camera;

void render(camera *cam, sphere_list *world);
static void initialise(camera *cam);
static colour ray_colour(ray r, sphere_list *world);
static vec3 sample_square();
static ray get_ray(camera *cam, int i, int j);

#endif