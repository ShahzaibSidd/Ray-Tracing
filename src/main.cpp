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

    //fat sphere to mimic floor
    std::shared_ptr<material> mat_s1 = std::make_shared<lambertian>(GREEN);
    objects.add(std::make_shared<sphere>(point_3d(0, -100.5, -1), 100, mat_s1));

    std::shared_ptr<material> mat_ground = std::make_shared<lambertian>(BLUE);
    objects.add(std::make_shared<sphere>(point_3d(0, 0, -1.2), 0.5, mat_ground));

    //hollow glass sphere
    std::shared_ptr<material> mat_s2 = std::make_shared<dielectric>(1.5);
    std::shared_ptr<material> mat_air_bubble = std::make_shared<dielectric>(1.0 / 1.5);
    objects.add(std::make_shared<sphere>(point_3d(-1, 0, -1), 0.5, mat_s2));
    objects.add(std::make_shared<sphere>(point_3d(-1, 0, -1), 0.4, mat_air_bubble));
    
    std::shared_ptr<material> mat_s3 = std::make_shared<metal>(GRAY, 1.0);
    objects.add(std::make_shared<sphere>(point_3d(1, 0, -1), 0.5, mat_s3));


        
    camera cam = camera();

    // control screen size and ratio
    cam.image_width_ = 400;
    cam.aspect_ratio_ = 16.0 / 9.0;

    // control vertical fov
    cam.vertical_fov_ = 20;

    // control camera position
    cam.look_from_ = point_3d(-2, 2, 1);
    cam.look_at_ = point_3d(0, 0, -1);

    // control focus blur
    cam.defocus_angle_ = 10.0;
    cam.focus_dist_ = 3.4;

    // control anti-aliasing
    cam.samples_per_pixel_ = 100;

    // control number of reflected rays
    cam.max_depth_ = 50;
    
    cam.render(objects);

    return 0;
}