#include "camera.hpp"
#include "constants.hpp"
#include "hittable_entity_list.hpp"
#include "sphere.hpp"

void make_pyramid(HittableEntityList &world) {
    int pyramid_width{8};
    double sphere_radius{0.5};
    double layer_offset{0};

    for (int layer = pyramid_width; layer > 0; --layer) {
        std::shared_ptr<Material> sphere_material;
        auto choose_mat{random_double()};

        if (choose_mat < 0.8) {
            // diffuse
            auto albedo{Colour::random() * Colour::random()};
            sphere_material = std::make_shared<Lambertian>(albedo);
        } else if (choose_mat < 0.98) {
            // metal
            auto albedo{Colour::random(0.5, 1)};
            auto fuzz{random_double(0, 0.5)};
            sphere_material = std::make_shared<Metal>(albedo, fuzz);
        } else {
            // glass
            sphere_material = std::make_shared<Dielectric>(1.5);
        }

        for (int width = 0; width < layer; ++width) {
            for (int depth = 0; depth < layer; ++depth) {
                auto pos{Point3(width + layer_offset,
                                ((pyramid_width - layer) / 2.0) + sphere_radius,
                                depth + layer_offset)};
                world.add(std::make_shared<Sphere>(pos, sphere_radius, sphere_material));
            }
        }

        layer_offset += sphere_radius;
    }
}

int main() {
    // World
    HittableEntityList world;

    auto ground_material{std::make_shared<Lambertian>(Colour(0.5, 0.5, 0.5))};
    world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    make_pyramid(world);

    Camera camera{};

    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 1920;
    camera.samples_per_pixel = 80;
    camera.max_depth = 50;

    camera.v_fov = 20;
    camera.look_from = Point3(18, 3, 18);
    camera.look_at = Point3(0, 2, 0);
    camera.v_up = Vec3(0, 1, 0);

    camera.defocus_angle = 0;
    camera.focus_dist = 18.0;

    camera.render(world);
}
