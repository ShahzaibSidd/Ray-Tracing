#include "ray.h"

ray::ray() {
    //empty
}

ray::ray(const point_3d& origin, const vec_3d& direction) {
    origin_ = origin;
    direction_ = direction;
}

const point_3d& ray::origin() const {
    return origin_;
}

const vec_3d& ray::direction() const {
    return direction_;
}

point_3d ray::at(double val) const {
    return (origin_ + (direction_ * val));
}

