#include "utility.hpp"

Colour ray_colour(const Ray &ray, const HittableEntity &hittable_entity);

int main() {
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    // Calculate the image height, and ensure that it's at least 1.
    auto image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // World
    HittableEntityList world;
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    auto focal_length = 1.0;
    auto camera_centre = Point3(0, 0, 0);

    // Viewport
    auto viewport_height = 2.0;
    // Viewport widths less than one are ok since they are real valued.
    // The aspect ratio could be used as the RH operand, however this is an ideal ratio and in
    // reality it is only approximate due to int rounding etc.
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = Vec3(viewport_width, 0, 0);
    // viewport_v y element negative as we start from top left and work downwards
    auto viewport_v = Vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left =
        camera_centre - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel_0_0_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel_0_0_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_centre;
            Ray ray(camera_centre, ray_direction);

            Colour pixel_colour = ray_colour(ray, world);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::clog << "Done! \n";
}

Colour ray_colour(const Ray &ray, const HittableEntity &hittable_entity) {
    HitRecord rec;

    if (hittable_entity.hit(ray, 0, INFINITY, rec)) {
        return 0.5 * (rec.normal + Colour(1, 1, 1));
    }

    Vec3 unit_direction = unit_vector(ray.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);

    return (1.0 - a) * Colour(1.0, 1.0, 1.0) + a * Colour(0.5, 0.7, 1.0);
}
