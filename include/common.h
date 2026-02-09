#pragma once


// common includes
#include <iostream>
#include <memory>
#include <limits>
#include <vector>
#include <cmath>


// miscellaneous useful functions
inline double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180;
}

inline double rand_double() {
    return (double) std::rand() / (RAND_MAX + 1.0);
}

inline double rand_double(double min, double max) {
    return min + ((max - min) * rand_double());
}