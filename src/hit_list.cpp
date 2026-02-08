#include "hit_list.h"

hit_list::hit_list() {
    //empty
};

hit_list::hit_list(std::shared_ptr<hittable> object) {
    add(object);
}

void hit_list::add(std::shared_ptr<hittable> object) {
    objects.push_back(object);
}

void hit_list::clear_list() {
    objects.clear();
}

bool hit_list::hit(const ray& curr_ray, interval curr_interval, hit_info& info) const {
    hit_info closest_hit;
    interval closest_interval = curr_interval;
    bool is_hit = false;
    
    for (const auto& object : objects) {
        if (object->hit(curr_ray, closest_interval, closest_hit)) {
            is_hit = true;
            closest_interval.max_ = closest_hit.t_val;

            info = closest_hit;
        }
    }

    return is_hit;
}