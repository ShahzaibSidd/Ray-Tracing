#pragma once

#include "vec_3d.h"

class ray {
    private:
    
    point_3d origin_;
    vec_3d direction_;      
    
    public:
        ray();
        ray(const point_3d& origin, const vec_3d& direction);
        const point_3d& origin() const;
        const vec_3d& direction() const;

        point_3d at(double val) const;
};