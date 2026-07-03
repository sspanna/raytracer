#include "hit_record.h"
#include "ray.h"
#include "sphere.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

// Direct equality is fine for values built from small integer arithmetic,
// but v3_normalize and v3_length involve sqrt(), so those need a tolerance.
#define EPS 1e-9
static int approx_eq(double a, double b) { return fabs(a - b) < EPS; }

static void assert_on_surface(sphere s, hit_record rec)
{
  // Distance from center to hit point must equal the radius.
  double dist = v3_length(v3_sub(rec.p, s.center));
  assert(approx_eq(dist, s.radius));
}

static void assert_normal_traces_back(sphere s, hit_record rec)
{
  // Normal must be a unit vector...
  assert(approx_eq(v3_length(rec.normal), 1.0));

  // ...and walking from center outward by `radius` along the normal
  // must land exactly back on the hit point.
  vec3 reconstructed_p = v3_add(s.center, v3_smul(rec.normal, s.radius));
  assert(approx_eq(reconstructed_p.x, rec.p.x));
  assert(approx_eq(reconstructed_p.y, rec.p.y));
  assert(approx_eq(reconstructed_p.z, rec.p.z));
}

void test_hit(void)
{
  sphere s = (sphere){
      .center = (point3){0, 0, -5},
      .radius = 1.0,
  };
  ray r = (ray){
      (point3){0, 0, 0},
      (vec3){0, 0, -1},
  };

  hit_record rec = {0};
  if (sphere_hit(s, r, 0, 10, &rec))
  {
    assert(rec.t == 4.0);
    assert(rec.p.z == -4.0);
  }
  else
  {
    assert(0);
  }
  printf("test sphere hit 1 passed\n");
}

void test_hit_bounds(void)
{
  sphere s = (sphere){
      .center = (point3){0, 0, -5},
      .radius = 1.0,
  };
  ray r = (ray){
      (point3){0, 0, 0},
      (vec3){0, 0, -1},
  };

  hit_record rec = {0};
  _Bool hit = sphere_hit(s, r, 7, 10, &rec);
  assert(hit == 0);
  printf("test sphere hit 2 - bounds passed\n");
}

void test_hit_miss(void)
{

  sphere s = (sphere){
      .center = (point3){5, 5, -5},
      .radius = 1.0,
  };
  ray r = (ray){
      (point3){0, 0, 0},
      (vec3){0, 0, -1},
  };

  hit_record rec = {0};
  _Bool hit = sphere_hit(s, r, 7, 10, &rec);
  assert(hit == 0);
  printf("test sphere miss 3 - miss passed\n");
}

void test_sphere_hit_near_root(void)
{
  sphere s = {.center = {0, 0, -5}, .radius = 1.0};
  ray r = {.orig = {0, 0, 0}, .dir = {0, 0, -1}};
  hit_record rec = {0};

  _Bool hit = sphere_hit(s, r, 1.0, 5.0, &rec);

  assert(hit == 1);
  assert(approx_eq(rec.t, 4.0));
  assert_on_surface(s, rec);
  assert_normal_traces_back(s, rec);
  printf("test_sphere_hit_near_root passed\n");
}

int main(void)
{
  test_hit();
  test_hit_bounds();
  test_hit_miss();
  test_sphere_hit_near_root();
  printf("All tests passed.\n");
  return 0;
}
