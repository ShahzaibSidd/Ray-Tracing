#pragma once

#include "common.h"

#include "ray.h"

struct hit_info {
    point_3d contact_point;
    double t_val;
    vec_3d normal;
    bool front_face;

    void set_normal_face(const ray& curr_ray, const vec_3d& outer_normal) {
            front_face = dot_product(curr_ray.direction(), outer_normal) < 0;
            normal = front_face ? outer_normal : outer_normal * -1.0;       
        }
};

class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& curr_ray, double min_t, double max_t, hit_info& info) const = 0;
};