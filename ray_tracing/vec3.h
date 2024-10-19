#ifndef VEC3_H
#define VEC3_H

typedef struct
{
    float x, y, z;
} vec3;

void init_vec3(vec3 *v, float x, float y, float z);
double v3x(vec3 v);
double v3y(vec3 v);
double v3z(vec3 v);
vec3 v3_add(vec3 v, vec3 u);
vec3 v3_subtract(vec3 v, vec3 u);
vec3 v3_multiply(vec3 v, vec3 u);
vec3 v3_scale(vec3 v, double scale);
double v3_dot(vec3 v, vec3 u);
vec3 v3_cross(vec3 v, vec3 u);
double v3_length(vec3 v);
vec3 v3_unit(vec3 v);

#endif