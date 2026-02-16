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

        double vertical_fov_ = 90;
        point_3d look_from_ = point_3d(0,0,0);
        point_3d look_at_ = point_3d(0,0,-1);
        vec_3d vup_ = vec_3d(0,1,0);
        
        vec_3d u_, v_, w_;

        double focal_length_;
        
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
        camera(int image_width, double aspect_ratio, double vertical_fov, 
               int samples_per_pixel, int max_depth, 
               point_3d look_from, point_3d look_at);

        void render(const hit_list& objects);
};