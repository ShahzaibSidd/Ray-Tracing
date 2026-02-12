#pragma once

#include "common.h"

class vec_3d {
    private:
        double x_ = 0;
        double y_ = 0;
        double z_ = 0;

    public:
        vec_3d();
        vec_3d(double x, double y, double z);

        double x() const;
        double y() const;
        double z() const;

        double length() const;
        double length_squared() const;
        
        bool near_zero() const;

        vec_3d operator-();
        vec_3d& operator+=(const vec_3d& vec);
        vec_3d& operator*=(double val);
        vec_3d& operator/=(double val);
        
        };
    
using point_3d = vec_3d;

inline vec_3d operator+(const vec_3d& u, const vec_3d& v) {
    vec_3d new_vec = vec_3d(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
    return new_vec;
}

inline vec_3d operator-(const vec_3d& u, const vec_3d& v) {
    vec_3d new_vec = vec_3d(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
    return new_vec;
}

inline vec_3d operator*(const vec_3d& u, const vec_3d& v) {
    vec_3d new_vec = vec_3d(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
    return new_vec;
}

inline vec_3d operator*(const vec_3d& u, double val) {
    vec_3d new_vec = vec_3d(u.x() * val, u.y() * val, u.z() * val);
    return new_vec;
}

inline vec_3d operator*(double val, const vec_3d& u) {
    vec_3d new_vec = u * val;
    return new_vec;
}

inline vec_3d operator/(const vec_3d& u, double val) {
    vec_3d new_vec = u * (1/val);
    return new_vec;
}

inline double dot_product(const vec_3d& u, const vec_3d& v) {
    double result = (u.x() * v.x()) + (u.y() * v.y()) + (u.z() * v.z());
    return result;
}

inline vec_3d cross_product(const vec_3d& u, const vec_3d& v) {
    vec_3d new_vec = vec_3d((u.y() * v.z()) - (u.z() * v.y()),
                            (u.z() * v.x()) - (u.x() * v.z()),
                            (u.x() * v.y()) - (u.y() * v.x())
                            );
    return new_vec;
}

inline vec_3d unit_vector(const vec_3d& u) {
    vec_3d new_vec = u / u.length();
    return new_vec;
}

inline vec_3d reflect(const vec_3d& u, const vec_3d& normal_vec) {
    return u - 2 * (dot_product(u, normal_vec) * normal_vec);
}

vec_3d rand_vec();
vec_3d rand_vec(double min, double max);
vec_3d rand_unit_vec();
vec_3d vec_on_hemisphere(const vec_3d& normal_vec);