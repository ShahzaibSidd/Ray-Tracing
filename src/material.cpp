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

dielectric::dielectric(double refractive_index) {
    refractive_index_ = refractive_index;
}

bool dielectric::scatter(const ray& input_ray, const hit_info& curr_info, colour& attenuated_colour, ray& scattered_ray) const {
    double rel_refractive_ind = (curr_info.front_face) ? (1.0 / refractive_index_) : refractive_index_;
    vec_3d unit_dir = unit_vector(input_ray.direction());
    
    vec_3d scattered_vec = refract(unit_dir, curr_info.normal, rel_refractive_ind);
    scattered_ray = ray(curr_info.contact_point, scattered_vec);
    
    attenuated_colour = colour(1.0, 1.0, 1.0);

    return true;
}