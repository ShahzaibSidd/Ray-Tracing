#include "camera.h"

#include <iomanip>

camera::camera() {
    //empty
}

camera::camera(int image_width, double aspect_ratio, int samples_per_pixel) {
    image_width_ = image_width;
    aspect_ratio_ = aspect_ratio;
    samples_per_pixel_ = samples_per_pixel;
}

void camera::init() {
    image_height_ = int(image_width_ / aspect_ratio_);
    if (image_height_ < 1) {
        image_height_ = 1;
    }

    focal_length_ = 1.0;
    viewport_height_ = 2.0;
    viewport_width_ = viewport_height_ * (double(image_width_) / image_height_);

    camera_origin_ = point_3d(0,0,0);

    viewport_u_ = vec_3d(viewport_width_, 0, 0);
    viewport_v_ = vec_3d(0, -viewport_height_, 0);

    delta_u_ = viewport_u_ / image_width_;
    delta_v_ = viewport_v_ / image_height_;
}


void camera::render(const hit_list& objects) {
    init();

    std::cout << "P3\n";
    std::cout << image_width_ << " " << image_height_ << "\n";
    std::cout << "255\n";

    point_3d viewport_top_left = camera_origin_ - point_3d(0,0,focal_length_) - viewport_u_/2 - viewport_v_/2;
    point_3d viewport_pixel_center = viewport_top_left + ((delta_u_ + delta_v_) / 2);

    for (int y = 0; y < image_height_; y++) {
        std::clog << std::fixed << std::setprecision(0) << "loading: " << (double)y/image_height_ * 100 << "\n" << std::flush;
        for (int x = 0; x < image_width_; x++) {
            point_3d pixel_center = viewport_pixel_center + (x * delta_u_) + (y * delta_v_);
            vec_3d ray_direction = pixel_center - camera_origin_;
            
            colour pixel;
            
            if (samples_per_pixel_ == 1) {
                ray curr_ray = ray(camera_origin_, ray_direction);
                pixel = ray_colour(curr_ray, objects);
            } else {
                for (int sample = 0; sample < samples_per_pixel_; sample++) {
                    ray sampled_ray = sample_ray(ray_direction);
                    pixel += ray_colour(sampled_ray, objects);
                }
            }
            
            write_colour(std::cout, pixel / samples_per_pixel_);


        }
    }
}

ray camera::sample_ray(const vec_3d& ray_direction) {
    double added_x = rand_double(-1, 1) * (delta_u_.length() / 2);
    double added_y = rand_double(-1, 1) * (delta_v_.length() / 2);
    
    vec_3d new_dir = vec_3d(ray_direction.x()+added_x, ray_direction.y()+added_y, ray_direction.z());
    return ray(camera_origin_, new_dir);
}

colour camera::ray_colour(const ray& r, const hit_list& objects) {
    hit_info curr_hit;
    if (objects.hit(r, interval(0, INFINITY), curr_hit)) {
        double r_val = 0.5 * (curr_hit.normal.x() + 1);
        double g_val = 0.5 * (curr_hit.normal.y() + 1);
        double b_val = 0.5 * (curr_hit.normal.z() + 1);
        return colour(r_val, g_val, b_val);
    }

    vec_3d unit_r = unit_vector(r.direction());
    double scaled_y = (unit_r.y() + 1.0) / 2.0;
    return (1.0-scaled_y) * colour(1.0, 1.0, 1.0) + scaled_y * colour(0.5, 0.7, 1.0);
}