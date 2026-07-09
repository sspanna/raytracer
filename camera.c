#include "camera.h"
#include "color.h"
#include "utils.h"
#include "vec3.h"
#include <math.h>

static color camera_ray_color(const ray r, const sphere_list all_spheres);

vec3 camera_sample_square()
{
  return (vec3){random_double() - 0.5, random_double() - 0.5, 0};
}

ray camera_get_ray(camera cam, int i, int j)
{
  vec3 offset = camera_sample_square();

  point3 current_pixel =
      v3_add(cam.pixel_zero, v3_smul(cam.pixel_delta_u, i + offset.x));
  current_pixel =
      v3_add(current_pixel, v3_smul(cam.pixel_delta_v, j + offset.y));
  vec3 ray_direction = v3_sub(current_pixel, cam.center);
  return (ray){cam.center, ray_direction};
}

void camera_render(camera cam, const sphere_list all_spheres)
{

  printf("P3\n");
  printf("%d %d\n", cam.image_width, cam.image_height);
  printf("255\n");

  for (int j = 0; j < cam.image_height; j++)
  {
    fprintf(stderr, "\rScanlines remaining: %d ", cam.image_height - j);
    fflush(stderr);

    for (int i = 0; i < cam.image_width; i++)
    {
      color pixel_color = (color){0, 0, 0};
      for (int sample = 0; sample < cam.samples_per_pixel; sample++)
      {
        ray r = camera_get_ray(cam, i, j);
        pixel_color = v3_add(pixel_color, camera_ray_color(r, all_spheres));
      }
      write_color(stdout, v3_smul(pixel_color, (1.0 / cam.samples_per_pixel)));
    }
  }
  fprintf(stderr, "\rDone.                    \n");
}

void camera_initialize(camera *cam)
{
  cam->samples_per_pixel = 10;
  cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
  cam->image_height = (cam->image_height < 1) ? 1 : cam->image_height;

  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * (double)(cam->image_width) / cam->image_height;

  cam->center =
      (point3){0, 0, 0}; // Vectors that goes across and down the viewport edges
  vec3 viewport_u = (vec3){viewport_width, 0, 0};

  // Note: y is flipped because bitmap y increases as it goes down
  vec3 viewport_v = (vec3){0, -viewport_height, 0};

  // Calculate the delta vectors (distance from a pixel to a neighbor pixel)
  cam->pixel_delta_u = v3_sdiv(viewport_u, cam->image_width);
  cam->pixel_delta_v = v3_sdiv(viewport_v, cam->image_height);

  // Calculate the location of the upper left pixel of viewport
  point3 viewport_upper_left = v3_sub(cam->center, (vec3){0, 0, focal_length});
  viewport_upper_left = v3_sub(viewport_upper_left, v3_sdiv(viewport_u, 2));
  viewport_upper_left = v3_sub(viewport_upper_left, v3_sdiv(viewport_v, 2));

  // printf("viewport: (%f, %f, %f)\n", viewport_upper_left.x,
  // viewport_upper_left.y, viewport_upper_left.z);
  cam->pixel_zero = v3_add(cam->pixel_delta_u, cam->pixel_delta_v);
  cam->pixel_zero = v3_smul(cam->pixel_zero, 0.5);
  cam->pixel_zero = v3_add(cam->pixel_zero, viewport_upper_left);
}

static color camera_ray_color(const ray r, const sphere_list all_spheres)
{
  hit_record rec;
  if (sphere_list_hit(all_spheres, r, (interval){0, INFINITY}, &rec))
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
