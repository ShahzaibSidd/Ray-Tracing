#pragma once

#include "vec_3d.h"
#include "ray.h"

class sphere{
    private:
        point_3d center_;
        double radius_;

    public:
        sphere();
        sphere(const point_3d& center, const double& radius);

        point_3d origin() const;
        double radius() const;
};

bool hit_sphere(const sphere& curr_sphere, const ray& curr_ray);