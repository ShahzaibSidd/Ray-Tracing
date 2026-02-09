#pragma once

#include "common.h"
#include "colour.h"

class camera {
    private:
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

        colour ray_colour(const ray& r, const hit_list& objects);
    
    public:
        camera();
        camera(int image_width, double aspect_ratio);

        void render(const hit_list& objects);
};