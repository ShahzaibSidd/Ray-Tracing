#pragma once

#include "common.h"

#include "hittable.h"
#include "vec_3d.h"
#include "ray.h"
#include "colour.h"

class sphere : public hittable {
    private:
        point_3d center_;
        double radius_;
        std::shared_ptr<material> mat_;

    public:
        sphere();
        sphere(const point_3d& center, const double& radius, std::shared_ptr<material> mat);

        point_3d center() const;
        double radius() const;
        
        bool hit(const ray& curr_ray, interval curr_interval, hit_info& info) const override;
};
