#pragma once

#include "common.h"

#include "hittable.h"

class hit_list : public hittable {
    private:
        std::vector<std::shared_ptr<hittable>> objects;

    public:
        hit_list();
        hit_list(std::shared_ptr<hittable> object);

        void add(std::shared_ptr<hittable> object);
        
        void clear_list();

        bool hit(const ray& curr_ray, double min_t, double max_t, hit_info& info) const override;
};