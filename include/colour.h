#pragma once

#include "vec_3d.h"
#include "ray.h"
#include "hit_list.h"

using colour = vec_3d;

void write_colour(std::ostream& out, const colour& curr_colour);

colour ray_colour(const ray& r, const hit_list& objects);