#include "sphere.h"

sphere::sphere() {
    center_ = point_3d(0,0,0);
    radius_ = 0;
    return;
}

sphere::sphere(const point_3d& center, const double& radius) {
    center_ = center;
    radius_ = (radius < 0) ? 0 : radius;
}

point_3d sphere::center() const {
    return center_;
}

double sphere::radius() const {
    return radius_;
}

bool sphere::hit(const ray& curr_ray, interval curr_interval, hit_info& info) const {
    vec_3d origin_to_center = center_ - curr_ray.origin();

    double a = curr_ray.direction().length_squared();
    double h = dot_product(curr_ray.direction(), center_ - curr_ray.origin());
    double c = origin_to_center.length_squared() - (radius_ * radius_);

    double discriminant = (h * h) - (a * c);

    if (discriminant < 0) {
        return false;
    }

    double sqrt_disc = std::sqrt(discriminant);
    double found_root = (h - sqrt_disc) / a;
    if (!curr_interval.contains(found_root)) {
        found_root = (h + sqrt_disc) / a;
        if (!curr_interval.contains(found_root)) {
            return false;
        }
    }
    
    info.t_val = found_root;
    info.contact_point = curr_ray.at(found_root);

    vec_3d normal = (info.contact_point - center_) / radius_;
    info.set_normal_face(curr_ray, normal);

    return true;
}