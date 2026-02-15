#include "camera.h"

#include <iomanip>

camera::camera() {
    //empty
}

camera::camera(int image_width, double aspect_ratio, double vertical_fov, int samples_per_pixel, int max_depth) {
    image_width_ = image_width;
    aspect_ratio_ = aspect_ratio;
    vertical_fov_ = vertical_fov;
    samples_per_pixel_ = samples_per_pixel;
    max_depth_ = max_depth;
}

void camera::init() {
    image_height_ = int(image_width_ / aspect_ratio_);
    if (image_height_ < 1) {
        image_height_ = 1;
    }

    focal_length_ = 1.0;

    double theta = degrees_to_radians(vertical_fov_);
    double h = std::tan(theta / 2);

    viewport_height_ = 2 * h * focal_length_;
    viewport_width_ = viewport_height_ * (double(image_width_) / image_height_);

    camera_origin_ = point_3d(0,0,0);

    viewport_u_ = vec_3d(viewport_width_, 0, 0);
    viewport_v_ = vec_3d(0, -viewport_height_, 0);

    delta_u_ = viewport_u_ / image_width_;
    delta_v_ = viewport_v_ / image_height_;
}

void camera::loading_bar(int y) {
    // goofy ahh loading bar
    std::clog << std::fixed << std::setprecision(0) << "LOADING: [";
    for (int completed = 0; completed < ((double)y / image_height_ * 10); completed++) {
        std::clog << std::fixed << "#";
    }
    for (int incompleted = 0; incompleted < (10 - (double)y / image_height_ * 10); incompleted++) {
        std::clog << " ";
    }
    std::clog << "] " << (double)y/image_height_ * 100 << "%        \r" << std::flush;
}

void camera::render(const hit_list& objects) {
    init();

    std::cout << "P3\n";
    std::cout << image_width_ << " " << image_height_ << "\n";
    std::cout << "255\n";

    point_3d viewport_top_left = camera_origin_ - point_3d(0,0,focal_length_) - viewport_u_/2 - viewport_v_/2;
    point_3d viewport_pixel_center = viewport_top_left + ((delta_u_ + delta_v_) / 2);

    for (int y = 0; y < image_height_; y++) {
        loading_bar(y);       
        for (int x = 0; x < image_width_; x++) {
            point_3d pixel_center = viewport_pixel_center + (x * delta_u_) + (y * delta_v_);
            vec_3d ray_direction = pixel_center - camera_origin_;
            
            colour pixel;
            
            if (samples_per_pixel_ == 1) {
                ray curr_ray = ray(camera_origin_, ray_direction);
                pixel = ray_colour(curr_ray, objects, 0);
            } else {
                for (int sample = 0; sample < samples_per_pixel_; sample++) {
                    ray sampled_ray = sample_ray(ray_direction);
                    pixel += ray_colour(sampled_ray, objects, 0);
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

colour camera::ray_colour(const ray& r, const hit_list& objects, int depth) {
    if (depth > max_depth_) {
        return colour(0, 0, 0);
    }

    hit_info curr_hit;
    if (objects.hit(r, interval(0.001, INFINITY), curr_hit)) {
        ray reflected_ray;
        colour attenuated_colour;
        if (curr_hit.mat->scatter(r, curr_hit, attenuated_colour, reflected_ray)) {
            return attenuated_colour * ray_colour(reflected_ray, objects, depth + 1);
        } else {
            return colour(0,0,0);
        }
    }

    vec_3d unit_r = unit_vector(r.direction());
    double scaled_y = (unit_r.y() + 1.0) / 2.0;
    return (1.0-scaled_y) * colour(1.0, 1.0, 1.0) + scaled_y * colour(0.5, 0.7, 1.0);
}

