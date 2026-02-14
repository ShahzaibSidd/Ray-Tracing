#pragma once

#include "common.h"

#include "hittable.h"
#include "colour.h"

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter(const ray& input_ray, const hit_info& curr_info, colour& attenuated_colour, ray& scattered_ray) const {
            return false;
        }
};

class lambertian : public material {
    private:
        colour albedo_;

    public:
        lambertian(const colour& albedo);
        bool scatter(const ray& input_ray, const hit_info& curr_info, colour& attenuated_colour, ray& scattered_ray) const override;

};

class metal : public material {
    private:
        colour albedo_;
        double fuzziness_;

    public:
        metal(const colour& albedo, double fuzz);
        bool scatter(const ray& input_ray, const hit_info& curr_info, colour& attenuated_colour, ray& scattered_ray) const override;

};

class dielectric : public material {
    private:
        double refractive_index_;

    public:
        dielectric(double refractive_index);
        bool scatter(const ray& input_ray, const hit_info& curr_info, colour& attenuated_colour, ray& scattered_ray) const override;

};