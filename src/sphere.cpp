#include "sphere.h"

sphere::sphere() {
    center_ = point_3d(0,0,0);
    radius_ = 0;
    return;
}

sphere::sphere(const point_3d& center, const double& radius) {
    center_ = center;
    radius_ = radius;
}

point_3d sphere::origin() const {
    return center_;
}

double sphere::radius() const {
    return radius_;
}

double hit_sphere(const sphere& curr_sphere, const ray& curr_ray) {
    vec_3d origin_to_center = curr_sphere.origin() - curr_ray.origin();

    double a = curr_ray.direction().length_squared();
    double b = -2.0 * dot_product(curr_ray.direction(), origin_to_center);
    double c = origin_to_center.length_squared() - (curr_sphere.radius() * curr_sphere.radius());

    double discriminant = (b * b) - (4 * a * c);

    //only take the front point for now
    return (discriminant >= 0) ? ((-b - std::sqrt(discriminant)) / (2.0 * a)) : -1.0;
}