#ifndef HITTABLE_ENTITY_HPP
#define HITTABLE_ENTITY_HPP

#include "interval.hpp"
#include "ray.hpp"

class Material;

class HitRecord {
  public:
    Point3 p;
    Vec3 normal;
    std::shared_ptr<Material> mat;
    double t;
    bool front_face;

    void set_face_normal(const Ray &ray, const Vec3 &outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class HittableEntity {
  public:
    virtual ~HittableEntity() = default;

    virtual bool hit(const Ray &ray, Interval ray_t, HitRecord &rec) const { return false; };
};

#endif
