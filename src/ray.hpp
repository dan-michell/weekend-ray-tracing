#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class Ray {
  public:
    Ray() = default;
    Ray(const Point3 &origin, const Vec3 &direction) : orig{origin}, dir{direction} {}

    const Point3 &origin() const { return orig; }
    const Vec3 &direction() const { return dir; }

    // Linear interpolation to get point at t
    Point3 at(double t) const { return orig + t * dir; }

  private:
    Point3 orig;
    Vec3 dir;
};

#endif
