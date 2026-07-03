#include "color.h"
#include "ray.h"
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

color ray_color(ray r)
{
  point3 circle_center = (point3){0, 0, -1};
  double t = hit_sphere(circle_center, 0.5, r);
  if (t > 0.0)
  {
    vec3 normal = v3_normalize(v3_sub(ray_at(r, t), circle_center));
    color color_at = (color){normal.x + 1, normal.y + 1, normal.z + 1};
    color_at = v3_smul(color_at, 0.5);
    return color_at;
  }
  vec3 unit_direction = v3_normalize(r.dir);
  double alpha = 0.5 * (unit_direction.y + 1.0);
  color white = (color){1, 1, 1};
  color blue = (color){.5, 0.7, 1};
  return v3_add(v3_smul(white, (1.0 - alpha)), v3_smul(blue, alpha));
}

int main(void)
{
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;

  // calculate image height based on aspect ratio
  int image_height = (int)(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Camera

  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * (double)(image_width) / image_height;
  point3 camera_center = (point3){0, 0, 0};

  // Vectors that goes across and down the viewport edges
  vec3 viewport_u = (vec3){viewport_width, 0, 0};
  // Note: y is flipped because bitmap y increases as it goes down
  vec3 viewport_v = (vec3){0, -viewport_height, 0};

  // Calculate the delta vectors (distance from a pixel to a neighbor pixel)
  vec3 pixel_delta_u = v3_sdiv(viewport_u, image_width);
  vec3 pixel_delta_v = v3_sdiv(viewport_v, image_height);

  // Calculate the location of the upper left pixel of viewport
  point3 viewport_upper_left =
      v3_sub(camera_center, (vec3){0, 0, focal_length});
  viewport_upper_left = v3_sub(viewport_upper_left, v3_sdiv(viewport_u, 2));
  viewport_upper_left = v3_sub(viewport_upper_left, v3_sdiv(viewport_v, 2));

  point3 pixel_zero = v3_add(pixel_delta_u, pixel_delta_v);
  pixel_zero = v3_smul(pixel_zero, 0.5);
  pixel_zero = v3_add(pixel_zero, viewport_upper_left);

  // Render
  printf("P3\n");
  printf("%d %d\n", image_width, image_height);
  printf("255\n");

  for (int j = 0; j < image_height; j++)
  {
    fprintf(stderr, "\rScanlines remaining: %d ", image_height - j);
    fflush(stderr);
    for (int i = 0; i < image_width; i++)
    {
      point3 current_pixel = v3_add(pixel_zero, v3_smul(pixel_delta_u, i));
      current_pixel = v3_add(current_pixel, v3_smul(pixel_delta_v, j));
      vec3 ray_direction = v3_sub(current_pixel, camera_center);
      ray r = (ray){camera_center, ray_direction};

      color pixel_color = ray_color(r);
      write_color(stdout, pixel_color);
    }
  }
  fprintf(stderr, "\rDone.                    \n");
  return 0;
}
