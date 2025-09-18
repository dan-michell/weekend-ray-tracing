#include "camera.hpp"
#include "constants.hpp"
#include "hittable_entity_list.hpp"
#include "sphere.hpp"

int main() {
    // World
    HittableEntityList world;

    auto ground_Material{std::make_shared<Lambertian>(Colour(0.5, 0.5, 0.5))};
    world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_Material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat{random_double()};
            Point3 centre(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((centre - Point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo{Colour::random() * Colour::random()};
                    sphere_material = std::make_shared<Lambertian>(albedo);

                    world.add(std::make_shared<Sphere>(centre, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo{Colour::random(0.5, 1)};
                    auto fuzz{random_double(0, 0.5)};
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);

                    world.add(std::make_shared<Sphere>(centre, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);

                    world.add(std::make_shared<Sphere>(centre, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Colour(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    Camera camera{};

    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 800;
    camera.samples_per_pixel = 10;
    camera.max_depth = 50;

    camera.v_fov = 90;
    camera.look_from = Point3(13, 2, 3);
    camera.look_at = Point3(0, 0, 0);
    camera.v_up = Vec3(0, 1, 0);

    camera.defocus_angle = 0.6;
    camera.focus_dist = 10.0;

    camera.render(world);
}
