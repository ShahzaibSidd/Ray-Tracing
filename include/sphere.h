#pragma once

#include "hittable.h"
#include "vec_3d.h"
#include "ray.h"

class sphere : public hittable {
    private:
        point_3d center_;
        double radius_;

    public:
        sphere();
        sphere(const point_3d& center, const double& radius);

        point_3d center() const;
        double radius() const;
        
        bool hit(const ray& curr_ray, double min_t, double max_t, hit_info& info) const override;
};
