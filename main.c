#include "camera.h"
#include "material.h"
#include "sphere_list.h"
#include "utils.h"
#include "vec3.h"
#include <unistd.h>

// @return t - parameter solution of intersecting point, or -1 for miss
int main(void)
{
  material mat_ground = (material){MATERIAL_LAMBERTIAN, (color){0.8, 0.8, 0.0}};
  material mat_center = (material){MATERIAL_LAMBERTIAN, (color){0.1, 0.2, 0.5}};
  material mat_right = (material){MATERIAL_METAL, (color){0.8, 0.6, 0.2}};
  // make some spheres
  sphere sphere1 = (sphere){
      (point3){0, 0, -1},
      0.5,
      mat_ground,
  };
  sphere sphere2 = (sphere){
      (point3){0, -100.5, -1},
      100,
      mat_center,
  };
  sphere sphere3 = (sphere){
      (point3){2, 1, -3},
      0.5,
      mat_right,
  };

  sphere_list all_spheres = sphere_list_new(10);
  sphere_list_add(&all_spheres, sphere1);
  sphere_list_add(&all_spheres, sphere2);
  sphere_list_add(&all_spheres, sphere3);

  // Camera
  camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;
  camera_initialize(&cam);
  // camera_print(cam);
  camera_render(cam, all_spheres);

  // Render
  return 0;
}
