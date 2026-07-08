#include "camera.h"
#include "color.h"
#include "hit_record.h"
#include "ray.h"
#include "sphere_list.h"
#include "vec3.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

// @return t - parameter solution of intersecting point, or -1 for miss
double hit_sphere(point3 center, double radius, ray r)
{
  vec3 oc = v3_sub(center, r.orig);
  double a = v3_dot(r.dir, r.dir);
  double h = v3_dot(r.dir, oc);
  double c = v3_dot(oc, oc) - radius * radius;
  double discriminant = h * h - a * c;
  if (discriminant < 0)
  {
    return -1.0;
  }
  else
  {
    return (h - sqrt(discriminant)) / a;
  }
}

int main(void)
{
  // make some spheres
  sphere sphere1 = (sphere){
      (point3){0, 0, -1},
      0.5,
  };
  sphere sphere2 = (sphere){
      (point3){0, -100.5, -1},
      100,
  };
  sphere sphere3 = (sphere){
      (point3){2, 1, -3},
      0.5,
  };

  sphere_list all_spheres = sphere_list_new(10);
  sphere_list_add(&all_spheres, sphere1);
  sphere_list_add(&all_spheres, sphere2);
  sphere_list_add(&all_spheres, sphere3);

  // Camera
  camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;

  camera_initialize(&cam);
  // camera_print(cam);
  camera_render(cam, all_spheres);

  // Render
  return 0;
}
