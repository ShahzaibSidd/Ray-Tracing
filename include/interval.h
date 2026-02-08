#pragma once

#include "common.h"

class interval {
    public:
        double min_;
        double max_;
        interval();
        interval(double min, double max);
        
        double size() const;
        
        bool contains(double val) const;
        bool surrounds(double val) const;

        static const interval empty;
        static const interval universe; 
};