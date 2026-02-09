#include <iomanip>

#include "common.h"

#include "vec_3d.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"
#include "colour.h"
#include "hittable.h"
#include "hit_list.h"

int main() {
    hit_list objects;
    objects.add(std::make_shared<sphere>(point_3d(0, 0, -1), 0.5));
    objects.add(std::make_shared<sphere>(point_3d(0, -100.5, -1), 100));


    int image_width = 400;
    double aspect_ratio = 16.0 / 9.0;

    camera cam = camera(image_width, aspect_ratio);
    cam.render(objects);

    return 0;

}