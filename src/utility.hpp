#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "colour.hpp"
#include "hittable_entity.hpp"
#include "hittable_entity_list.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

// Constants
const double PI = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) { return degrees * PI / 180.0; }

#endif
