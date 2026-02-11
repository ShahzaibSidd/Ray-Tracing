#include "colour.h"

void write_colour(std::ostream& out, const colour& curr_colour) {
    static const interval intensity = interval(0, 0.999);

    double r_val = gamma_correct(curr_colour.x());
    double g_val = gamma_correct(curr_colour.y());
    double b_val = gamma_correct(curr_colour.z());

    r_val = int(255.9999 * intensity.clamp(r_val));
    g_val = int(255.9999 * intensity.clamp(g_val));
    b_val = int(255.9999 * intensity.clamp(b_val));


    out << r_val << " " << g_val << " " << b_val << "\n";

    return;
}

colour ray_colour(const ray& r, const hit_list& objects) {
    hit_info curr_hit;
    if (objects.hit(r, interval(0, INFINITY), curr_hit)) {
        double r_val = 0.5 * (curr_hit.normal.x() + 1);
        double g_val = 0.5 * (curr_hit.normal.y() + 1);
        double b_val = 0.5 * (curr_hit.normal.z() + 1);
        return colour(r_val, g_val, b_val);
    }

    vec_3d unit_r = unit_vector(r.direction());
    double scaled_y = (unit_r.y() + 1.0) / 2.0;
    return (1.0-scaled_y) * colour(1.0, 1.0, 1.0) + scaled_y * colour(0.5, 0.7, 1.0);
}

double gamma_correct(double colour_val) {
    if (colour_val > 0) {
        return std::sqrt(colour_val);
    }
    return 0;
}