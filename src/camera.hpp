#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "colour.hpp"
#include "hittable_entity.hpp"
#include "material.hpp"
#include "random.hpp"
#include "utility.hpp"

class Camera {
  public:
    int image_width{800};
    double aspect_ratio{16.0 / 9.0};
    int samples_per_pixel{100};
    int max_depth{10};

    // Initialise camera view / orientation parameters
    double v_fov{90};
    Point3 look_from{0, 0, 0};
    Point3 look_at{0, 0, -1};
    Vec3 v_up{0, 1, 0}; // Camera relative up direction

    double defocus_angle{0}; // Variation angle of rays through each pixel
    double focus_dist{10};   // Distance from camera lookfrom point to plane of perfect focus

    Camera() = default;

    void render(const HittableEntity &world) {
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

            for (int i = 0; i < image_width; i++) {
                Colour pixel_colour{0, 0, 0};

                for (int sample = 0; sample < samples_per_pixel; ++sample) {
                    Ray ray = get_ray(i, j);
                    pixel_colour += ray_colour(ray, world, max_depth);
                }

                write_colour(std::cout, pixel_samples_scale * pixel_colour);
            }
        }

        std::clog << "Done! \n";
    }

  private:
    int image_height{};
    Point3 camera_centre{};
    Vec3 pixel_delta_u{}, pixel_delta_v{};
    Vec3 pixel_0_0_loc{};
    double pixel_samples_scale{};
    Vec3 u{}, v{}, w{};                      // Camera frame basis vectors
    Vec3 defocus_disk_u{}, defocus_disk_v{}; // Defocus disk horizontal and vertical radius

    void initialize() {
        std::clog << "Initialising camera...\n";

        // Calculate the image height, and ensure that it's at least 1.
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        camera_centre = look_from;

        // Viewport
        auto theta = degrees_to_radians(v_fov);
        auto h = std::tan(theta / 2);
        auto viewport_height = 2 * h * focus_dist;
        // Viewport widths less than one are ok since they are real valued.
        // The aspect ratio could be used as the RH operand, however this is an ideal ratio and in
        // reality it is only approximate due to int rounding etc.
        auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

        // Calculate the camera basis vectors
        w = unit_vector(look_from - look_at);
        u = unit_vector(cross(v_up, w));
        v = cross(w, u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = viewport_width * u;
        // viewport_v y element negative as we start from top left and work downwards
        auto viewport_v = viewport_height * -v;

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            camera_centre - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
        pixel_0_0_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // Calculate the camera defocus disk basis vectors. tan = O/A
        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    Ray get_ray(int i, int j) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.
        auto offset{sample_square()};
        auto pixel_sample{pixel_0_0_loc + ((i + offset.x()) * pixel_delta_u) +
                          ((j + offset.y()) * pixel_delta_v)};

        auto ray_origin{(defocus_angle <= 0) ? camera_centre : defocus_disk_sample()};
        auto ray_direction = pixel_sample - ray_origin;

        return Ray{ray_origin, ray_direction};
    }

    Point3 defocus_disk_sample() const {
        auto p{random_in_unit_disk()};

        return camera_centre + (p.x() * defocus_disk_u) + (p.y() * defocus_disk_v);
    }

    static Colour ray_colour(const Ray &ray, const HittableEntity &hittable_entity, int depth) {
        if (depth <= 0) {
            return Colour{0, 0, 0};
        }

        HitRecord rec;

        if (hittable_entity.hit(ray, Interval(0.001, INF), rec)) {
            Ray scattered{};
            Colour attenuation{};

            if (rec.mat->scatter(ray, rec, attenuation, scattered))
                return attenuation * ray_colour(scattered, hittable_entity, --depth);

            return Colour{0, 0, 0};
        }

        Vec3 unit_direction = unit_vector(ray.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);

        return (1.0 - a) * Colour(1.0, 1.0, 1.0) + a * Colour(0.5, 0.7, 1.0);
    }

    static Vec3 sample_square() {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return Vec3{random_double() - 0.5, random_double() - 0.5, 0};
    }
};

#endif
