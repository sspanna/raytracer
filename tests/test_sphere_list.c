#include "sphere_list.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define EPS 1e-9
static int approx_eq(double a, double b) { return fabs(a - b) < EPS; }

void test_sphere_list_empty(void)
{
  sphere_list list = sphere_list_new(4);
  ray r = {.orig = {0, 0, 0}, .dir = {0, 0, -1}};
  hit_record rec = {0};

  _Bool hit = sphere_list_hit(list, r, 0.001, 100.0, &rec);

  assert(hit == 0);
  sphere_list_free(&list);
  printf("test_sphere_list_empty passed\n");
}

void test_sphere_list_single_hit(void)
{
  sphere_list list = sphere_list_new(4);
  sphere_list_add(&list, (sphere){.center = {0, 0, -5}, .radius = 1.0});

  ray r = {.orig = {0, 0, 0}, .dir = {0, 0, -1}};
  hit_record rec = {0};

  _Bool hit = sphere_list_hit(list, r, 0.001, 100.0, &rec);

  assert(hit == 1);
  assert(approx_eq(rec.t, 4.0)); // sphere surface at distance 5-1=4

  sphere_list_free(&list);
  printf("test_sphere_list_single_hit passed\n");
}

void test_sphere_list_single_miss(void)
{
  sphere_list list = sphere_list_new(4);
  // Sphere well off to the side -- ray straight down -Z never reaches it.
  sphere_list_add(&list, (sphere){.center = {5, 5, -5}, .radius = 1.0});

  ray r = {.orig = {0, 0, 0}, .dir = {0, 0, -1}};
  hit_record rec = {0};

  _Bool hit = sphere_list_hit(list, r, 0.001, 100.0, &rec);

  assert(hit == 0);
  sphere_list_free(&list);
  printf("test_sphere_list_single_miss passed\n");
}

// Near sphere added FIRST, far sphere added SECOND -- closest tracking
// must still shrink the range as the near sphere is found.
void test_sphere_list_closest_wins_near_first(void)
{
  sphere_list list = sphere_list_new(4);
  sphere_list_add(
      &list, (sphere){.center = {0, 0, -5}, .radius = 1.0}); // surface at t=4
  sphere_list_add(
      &list, (sphere){.center = {0, 0, -10}, .radius = 1.0}); // surface at t=9

  ray r = {.orig = {0, 0, 0}, .dir = {0, 0, -1}};
  hit_record rec = {0};

  _Bool hit = sphere_list_hit(list, r, 0.001, 100.0, &rec);

  assert(hit == 1);
  assert(approx_eq(rec.t, 4.0)); // must report the NEAR sphere, not the far one

  sphere_list_free(&list);
  printf("test_sphere_list_closest_wins_near_first passed\n");
}

// Same two spheres, added in the OPPOSITE order -- this is the case that
// actually catches a bug in the closest-so-far tracking, since without it,
// "last sphere checked" would silently win instead of "nearest sphere."
void test_sphere_list_closest_wins_far_first(void)
{
  sphere_list list = sphere_list_new(4);
  sphere_list_add(
      &list, (sphere){.center = {0, 0, -10}, .radius = 1.0}); // surface at t=9
  sphere_list_add(
      &list, (sphere){.center = {0, 0, -5}, .radius = 1.0}); // surface at t=4

  ray r = {.orig = {0, 0, 0}, .dir = {0, 0, -1}};
  hit_record rec = {0};

  _Bool hit = sphere_list_hit(list, r, 0.001, 100.0, &rec);

  assert(hit == 1);
  assert(approx_eq(rec.t,
                   4.0)); // still the near sphere, despite being checked last

  sphere_list_free(&list);
  printf("test_sphere_list_closest_wins_far_first passed\n");
}

int main(void)
{
  test_sphere_list_empty();
  test_sphere_list_single_hit();
  test_sphere_list_single_miss();
  test_sphere_list_closest_wins_near_first();
  test_sphere_list_closest_wins_far_first();
  printf("All sphere_list tests passed.\n");
  return 0;
}
