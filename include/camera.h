#pragma once

#include "common.h"
#include "colour.h"
#include "material.h"

class camera {
    private:
        int samples_per_pixel_ = 1;

        int max_depth_ = 10;

        double aspect_ratio_ = 1.0;
        int image_width_ = 100;
        int image_height_;
        
        int focal_length_;
        double viewport_height_;
        double viewport_width_;

        point_3d camera_origin_;

        vec_3d viewport_u_;
        vec_3d viewport_v_;

        vec_3d delta_u_;
        vec_3d delta_v_;
    
        void init();
        void loading_bar(int y);

        colour ray_colour(const ray& r, const hit_list& objects, int depth);

        ray sample_ray(const vec_3d& ray_direction);
    
    public:
        camera();
        camera(int image_width, double aspect_ratio, int samples_per_pixel, int max_depth);

        void render(const hit_list& objects);
};