#include "material.h"

lambertian::lambertian(const colour& albedo) {
    albedo_ = albedo;
}

bool lambertian::scatter(const ray& input_ray, const hit_info& curr_info, colour& attenuated_colour, ray& scattered_ray) const {
    vec_3d scattered_vec = curr_info.normal + rand_unit_vec();
    if (scattered_vec.near_zero()) {
        scattered_vec = curr_info.normal;
    }
    
    scattered_ray = ray(curr_info.contact_point, scattered_vec);
    attenuated_colour = albedo_;
    return true;
}

metal::metal(const colour& albedo) {
    albedo_ = albedo;
}

bool metal::scatter(const ray& input_ray, const hit_info& curr_info, colour& attenuated_colour, ray& scattered_ray) const {
    vec_3d scattered_vec = reflect(input_ray.direction(), curr_info.normal);  
    scattered_ray = ray(curr_info.contact_point, scattered_vec);
    attenuated_colour = albedo_;
    return true;
}