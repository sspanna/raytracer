#pragma once
#include "color.h"
#include "sphere_list.h"
#include "vec3.h"

typedef struct
{
  double aspect_ratio;
  int image_width;
  int image_height;

  // internals
  point3 center;
  point3 pixel_zero;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;

} camera;

color ray_color(const ray r, const sphere_list world);

void camera_render(camera cam, const sphere_list spheres);

void camera_initialize(camera *cam);

static inline void camera_print(camera cam)
{
  printf("Camera\n");
  printf("dimensions: (%d, %d)", cam.image_width, cam.image_height);
  printf("center: (%f, %f, %f)", cam.center.x, cam.center.y, cam.center.z);
  printf("Upper Left: (%f, %f)", cam.pixel_zero.x, cam.pixel_zero.y);
  printf("pixel_delta: (%f, %f)", cam.pixel_delta_u.x, cam.pixel_delta_u.y);
}
