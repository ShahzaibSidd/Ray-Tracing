#pragma once

#include "common.h"
#include "colour.h"
#include "material.h"

class camera {
    private:       
        int image_height_;

        vec_3d u_, v_, w_;

        double focal_length_;
        
        double viewport_height_;
        double viewport_width_;

        point_3d camera_origin_;

        vec_3d viewport_u_;
        vec_3d viewport_v_;

        vec_3d delta_u_;
        vec_3d delta_v_;

        vec_3d defocus_disk_u_;
        vec_3d defocus_disk_v_;
    
        void init();
        void loading_bar(int y);

        colour ray_colour(const ray& r, const hit_list& objects, int depth) const;

        ray sample_ray(const point_3d& origin, const point_3d& pixel_center) const;

        point_3d sample_defocus_disk() const;
    
    public:
        int samples_per_pixel_ = 1;

        int max_depth_ = 10;

        double aspect_ratio_ = 1.0;
        int image_width_ = 100;

        double vertical_fov_ = 90;
        point_3d look_from_ = point_3d(0,0,0);
        point_3d look_at_ = point_3d(0,0,-1);
        vec_3d vup_ = vec_3d(0,1,0);

        double defocus_angle_ = 0;
        double focus_dist_ = 10;
        camera();

        void render(const hit_list& objects);
};