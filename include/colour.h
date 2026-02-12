#pragma once

#include "common.h"

#include "vec_3d.h"
#include "ray.h"
#include "hit_list.h"
#include "interval.h"

using colour = vec_3d;

// common colours
const colour GREEN = colour(0.8, 0.8, 0);
const colour BLUE = colour(0.1, 0.2, 0.5);
const colour GRAY = colour(0.8, 0.8, 0.8);
const colour YELLOW = colour(0.8, 0.6, 0.2);

void write_colour(std::ostream& out, const colour& curr_colour);

colour ray_colour(const ray& r, const hit_list& objects);

double gamma_correct(double colour_val);