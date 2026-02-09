#include "interval.h"

interval::interval() {
    min_ = INFINITY;
    max_= -INFINITY;
}

interval::interval(double min, double max) {
    min_ = min;
    max_ = max;
}

double interval::size() const {
    return max_ - min_;
}

bool interval::contains(double val) const {
    return (min_ <= val && val <= max_) ? true : false;
}

bool interval::surrounds(double val) const {
    return (min_ < val && val < max_) ? true : false;
}

double interval::clamp(double val) const {
    if (val < min_) return min_;
    if (val > max_) return max_;
    return val;
}

const interval interval::empty = interval(INFINITY, -INFINITY);
const interval interval::universe = interval(-INFINITY, INFINITY);
