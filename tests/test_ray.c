#include "ray.h"
#include <assert.h>
#include <stdio.h>

void test_ray_at(void)
{
  point3 orig = (point3){0, 0, 0};
  vec3 dir = (vec3){1, 0, 0};

  ray r = (ray){orig, dir};
  vec3 P = ray_at(r, 0.5);

  assert(P.x == 0.5 && P.y == 0 && P.z == 0);
  printf("test_ray_at passed\n");
}

void test_ray_at_zero(void)
{
  point3 orig = (point3){0, 0, 0};
  vec3 dir = (vec3){1, 0, 0};

  ray r = (ray){orig, dir};
  vec3 P = ray_at(r, 0.0);

  assert(P.x == orig.x && P.y == orig.y && P.z == orig.z);
  printf("test_ray_at_zero passed\n");
}

void test_ray_at_neg(void)
{
  point3 orig = (point3){0, 0, 0};
  vec3 dir = (vec3){1, 0, 0};

  ray r = (ray){orig, dir};
  vec3 P = ray_at(r, -1.0);

  assert(P.x == -1.0 && P.y == 0.0 && P.z == 0.0);
  printf("test_ray_at_neg passed\n");
}
int main(void)
{
  test_ray_at();
  test_ray_at_zero();
  test_ray_at_neg();
  printf("All ray tests passed.\n");
  return 0;
}
