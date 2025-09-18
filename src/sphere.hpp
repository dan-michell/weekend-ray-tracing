#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable_entity.hpp"

class Sphere : public HittableEntity {
  public:
    Sphere(const Point3 &center, double radius, std::shared_ptr<Material> mat)
        : center{center}, radius{std::fmax(0, radius)}, mat{mat} {}

    bool hit(const Ray &ray, Interval ray_t, HitRecord &rec) const override {
        Vec3 oc = center - ray.origin();
        auto a = ray.direction().length_squared();
        auto h = dot(ray.direction(), oc);
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = h * h - a * c;

        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;

        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;

            if (!ray_t.surrounds(root)) {
                return false;
            }
        }

        rec.t = root;
        rec.p = ray.at(rec.t);
        Vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(ray, outward_normal);
        rec.mat = mat;

        return true;
    }

  private:
    Point3 center;
    double radius;
    std::shared_ptr<Material> mat;
};

#endif
