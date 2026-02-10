#include "vec_3d.h"

vec_3d::vec_3d() {
    //empty
}

vec_3d::vec_3d(double x, double y, double z) {
    x_ = x;
    y_ = y;
    z_ = z;
    return;
}

double vec_3d::x() const {
    return x_;
}

double vec_3d::y() const {
    return y_;
}

double vec_3d::z() const {
    return z_;
}

vec_3d vec_3d::operator-() {
    return vec_3d(-x_, -y_, -z_);
}

vec_3d& vec_3d::operator+=(const vec_3d& vec) {
    x_ += vec.x_;
    y_ += vec.y_;
    z_ += vec.z_;
    return *this;
}

vec_3d& vec_3d::operator*=(double val) {
    x_ *= val;
    y_ *= val;
    z_ *= val;
    return *this;
}

vec_3d& vec_3d::operator/=(double val) {
    x_ *= 1/val;
    y_ *= 1/val;
    z_ *= 1/val;
    return *this;
}

double vec_3d::length() const {
    return sqrt((x_*x_) + (y_*y_) + (z_*z_));
}

double vec_3d::length_squared() const {
    return (x_*x_) + (y_*y_) + (z_*z_);
}

vec_3d rand_vec() {
    return vec_3d(rand_double(), rand_double(), rand_double());
}

vec_3d rand_vec(double min, double max) {
    return vec_3d(rand_double(min, max), rand_double(min, max), rand_double(min, max));
}

vec_3d rand_unit_vec() {
    vec_3d curr_vec = rand_vec(-1.0, 1.0);
    double len_sq = curr_vec.length_squared();
 
    while (len_sq > 1 || len_sq < 1e-10) {
        curr_vec = rand_vec(-1.0, 1.0);
        len_sq = curr_vec.length_squared();
    }
 
    return (curr_vec / curr_vec.length());
}

vec_3d vec_on_hemisphere(const vec_3d& normal_vec) {
    vec_3d curr_vec = rand_unit_vec();
    double dot_prod = dot_product(curr_vec, normal_vec);

    return (dot_prod >= 0) ? curr_vec : (curr_vec * -1.0);
}