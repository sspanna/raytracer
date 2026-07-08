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

color ray_color(ray r, sphere_list all_spheres)
{
  hit_record rec;
  if (sphere_list_hit(all_spheres, r, 0, INFINITY, &rec))
  {
    return v3_smul(
        (color){rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1}, 0.5);
  }
  // background
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

      color pixel_color = ray_color(r, all_spheres);
      write_color(stdout, pixel_color);
    }
  }
  fprintf(stderr, "\rDone.                    \n");
  return 0;
}
