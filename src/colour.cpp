#include "colour.h"
#include "sphere.h"

void write_colour(std::ostream& out, const colour& curr_colour) {
    int r_val = int(255.9999 * curr_colour.x());
    int g_val = int(255.9999 * curr_colour.y());
    int b_val = int(255.9999 * curr_colour.z());

    out << r_val << " " << g_val << " " << b_val << "\n";

    return;
}

colour ray_colour(const ray& r) {
    const sphere curr_sphere = sphere(point_3d(0,0,-1), 0.5);
    if (hit_sphere(curr_sphere, r)) {
        return colour(0, 1, 0);
    }

    vec_3d unit_r = unit_vector(r.direction());
    double scaled_y = (unit_r.y() + 1.0) / 2.0;
    return (1.0-scaled_y) * colour(1.0, 1.0, 1.0) + scaled_y * colour(0.5, 0.7, 1.0);
}