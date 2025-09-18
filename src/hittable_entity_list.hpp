#ifndef HITTABLE_ENTITY_LIST_HPP
#define HITTABLE_ENTITY_LIST_HPP

#include "hittable_entity.hpp"

#include <vector>

class HittableEntityList : public HittableEntity {
  public:
    std::vector<std::shared_ptr<HittableEntity>> hittable_entities{};

    HittableEntityList() = default;
    explicit HittableEntityList(const std::shared_ptr<HittableEntity> hittable_entity) {
        add(hittable_entity);
    }

    void clear() { hittable_entities.clear(); }

    void add(const std::shared_ptr<HittableEntity> hittable_entity) {
        hittable_entities.push_back(hittable_entity);
    }

    bool hit(const Ray &ray, Interval ray_t, HitRecord &rec) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto &hittable_entity : hittable_entities) {
            if (hittable_entity->hit(ray, Interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif
