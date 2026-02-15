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

metal::metal(const colour& albedo, double fuzz) {
    albedo_ = albedo;
    fuzziness_ = (fuzz < 1) ? fuzz : 1;
}

bool metal::scatter(const ray& input_ray, const hit_info& curr_info, colour& attenuated_colour, ray& scattered_ray) const {
    vec_3d scattered_vec = reflect(input_ray.direction(), curr_info.normal);
    scattered_vec = unit_vector(scattered_vec) + (rand_unit_vec() * fuzziness_); 
    scattered_ray = ray(curr_info.contact_point, scattered_vec);
    attenuated_colour = albedo_;
    return (dot_product(scattered_vec, curr_info.normal) > 0);
}

double dielectric::reflectance(double cos, double refractive_ind) const {
    double r0 = (1 - refractive_ind) / (1 + refractive_ind);
    r0 *= r0;
    return r0 + (1 - r0) * std::pow((1 - cos), 5);
}

dielectric::dielectric(double refractive_index) {
    refractive_index_ = refractive_index;
}

bool dielectric::scatter(const ray& input_ray, const hit_info& curr_info, colour& attenuated_colour, ray& scattered_ray) const {
    double rel_refractive_ind = (curr_info.front_face) ? (1.0 / refractive_index_) : refractive_index_;
    vec_3d unit_dir = unit_vector(input_ray.direction());


    double cos_val = dot_product(unit_dir * -1.0, curr_info.normal);
    if (cos_val > 1.0) {
        cos_val = 1.0;
    }
    double sin_val = std::sqrt(1.0 - (cos_val * cos_val));

    bool tir = rel_refractive_ind * sin_val > 1.0;
    bool shlick_approx = reflectance(cos_val, rel_refractive_ind) > rand_double();

    vec_3d scattered_vec;
    if (tir || shlick_approx) {
        scattered_vec = reflect(unit_dir, curr_info.normal);
    } else {
        scattered_vec = refract(unit_dir, curr_info.normal, rel_refractive_ind);
    }
    
    scattered_ray = ray(curr_info.contact_point, scattered_vec);
    
    attenuated_colour = colour(1.0, 1.0, 1.0);

    return true;
}