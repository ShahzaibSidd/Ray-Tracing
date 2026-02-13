#include <iomanip>

#include "common.h"

#include "vec_3d.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"
#include "colour.h"
#include "hittable.h"
#include "material.h"
#include "hit_list.h"

int main() {
    hit_list objects;
    
    std::shared_ptr<material> mat_ground = std::make_shared<lambertian>(BLUE);
    objects.add(std::make_shared<sphere>(point_3d(0, 0, -1.2), 0.5, mat_ground));

    std::shared_ptr<material> mat_s1 = std::make_shared<lambertian>(GREEN);
    objects.add(std::make_shared<sphere>(point_3d(0, -100.5, -1), 100, mat_s1));

    std::shared_ptr<material> mat_s2 = std::make_shared<metal>(YELLOW, 0.4);
    objects.add(std::make_shared<sphere>(point_3d(-1, 0, -1), 0.5, mat_s2));

    std::shared_ptr<material> mat_s3 = std::make_shared<metal>(GRAY, 1.0);
    objects.add(std::make_shared<sphere>(point_3d(1, 0, -1), 0.5, mat_s3));


    // control screen size and ratio
    int image_width = 400;
    double aspect_ratio = 16.0 / 9.0;

    // control anti-aliasing
    int samples_per_pixel = 50;

    // control number of reflected rays
    int max_depth = 50;


    camera cam = camera(image_width, aspect_ratio, samples_per_pixel, max_depth);
    cam.render(objects);

    return 0;

}