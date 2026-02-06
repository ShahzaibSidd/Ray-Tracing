#include <iostream>
#include <iomanip>

#include "vec_3d.h"
#include "ray.h"
#include "sphere.h"
#include "colour.h"

int main() {

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    if (image_height < 1) {
        image_height = 1;
    }

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(image_width) / image_height);

    point_3d camera_origin = point_3d(0,0,0);

    vec_3d viewport_u = vec_3d(viewport_width, 0, 0);
    vec_3d viewport_v = vec_3d(0, -viewport_height, 0);

    vec_3d delta_u = viewport_u / image_width;
    vec_3d delta_v = viewport_v / image_height;

    point_3d viewport_top_left = camera_origin - point_3d(0,0,focal_length) - viewport_u/2 - viewport_v/2;
    point_3d viewport_pixel_center = viewport_top_left + ((delta_u + delta_v) / 2);
    
    std::cout << "P3\n";
    std::cout << image_width << " " << image_height << "\n";
    std::cout << "255\n";
    
    for (int y = 0; y < image_height; y++) {
        std::clog << std::fixed << std::setprecision(0) << "loading: " << (double)y/image_height * 100 << "\n" << std::flush;
        for (int x = 0; x < image_width; x++) {
            point_3d pixel_center = viewport_pixel_center + (x * delta_u) + (y * delta_v);
            vec_3d ray_direction = pixel_center - camera_origin;

            ray curr_ray = ray(camera_origin, ray_direction);

            colour pixel = ray_colour(curr_ray);
            write_colour(std::cout, pixel);
        }
    }

    return 0;

}