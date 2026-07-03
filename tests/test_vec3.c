// test_vec3.c
#include "vec3.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

// Direct equality is fine for values built from small integer arithmetic,
// but v3_normalize and v3_length involve sqrt(), so those need a tolerance.
#define EPS 1e-9
static int approx_eq(double a, double b) { return fabs(a - b) < EPS; }

void test_v3_add(void)
{
  vec3 u = {1.0, 2.0, 3.0};
  vec3 v = {4.0, 5.0, 6.0};
  vec3 r = v3_add(u, v);
  assert(r.x == 5.0 && r.y == 7.0 && r.z == 9.0);
  printf("test_v3_add passed\n");
}

void test_v3_sub(void)
{
  vec3 u = {4.0, 5.0, 6.0};
  vec3 v = {1.0, 2.0, 3.0};
  vec3 r = v3_sub(u, v);
  assert(r.x == 3.0 && r.y == 3.0 && r.z == 3.0);
  printf("test_v3_sub passed\n");
}

void test_v3_neg(void)
{
  vec3 u = {1.0, -2.0, 3.0};
  vec3 r = v3_neg(u);
  assert(r.x == -1.0 && r.y == 2.0 && r.z == -3.0);
  printf("test_v3_neg passed\n");
}

void test_v3_mul(void)
{
  vec3 u = {2.0, 3.0, 4.0};
  vec3 v = {5.0, 6.0, 7.0};
  vec3 r = v3_mul(u, v);
  assert(r.x == 10.0 && r.y == 18.0 && r.z == 28.0);
  printf("test_v3_mul passed\n");
}

void test_v3_dot(void)
{
  vec3 u = {1.0, 2.0, 3.0};
  vec3 v = {4.0, 5.0, 6.0};
  // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
  double r = v3_dot(u, v);
  assert(r == 32.0);
  printf("test_v3_dot passed\n");
}

void test_v3_cross(void)
{
  // Textbook case: x cross y = z (right-hand rule)
  vec3 x = {1.0, 0.0, 0.0};
  vec3 y = {0.0, 1.0, 0.0};
  vec3 r = v3_cross(x, y);
  assert(r.x == 0.0 && r.y == 0.0 && r.z == 1.0);

  // And y cross x = -z, to catch a swapped sign in the formula
  vec3 r2 = v3_cross(y, x);
  assert(r2.x == 0.0 && r2.y == 0.0 && r2.z == -1.0);
  printf("test_v3_cross passed\n");
}

void test_v3_smul(void)
{
  vec3 u = {1.0, 2.0, 3.0};
  vec3 r = v3_smul(u, 2.0);
  assert(r.x == 2.0 && r.y == 4.0 && r.z == 6.0);
  printf("test_v3_smul passed\n");
}

void test_v3_sdiv(void)
{
  vec3 u = {2.0, 4.0, 6.0};
  vec3 r = v3_sdiv(u, 2.0);
  assert(r.x == 1.0 && r.y == 2.0 && r.z == 3.0);
  printf("test_v3_sdiv passed\n");
}

void test_v3_length_squared(void)
{
  vec3 u = {3.0, 4.0, 0.0};
  // 3-4-5 triangle: length_squared should be 25, avoiding sqrt entirely
  double r = v3_length_squared(u);
  assert(r == 25.0);
  printf("test_v3_length_squared passed\n");
}

void test_v3_length(void)
{
  vec3 u = {3.0, 4.0, 0.0};
  double r = v3_length(u);
  assert(approx_eq(r, 5.0));
  printf("test_v3_length passed\n");
}

void test_v3_normalize(void)
{
  vec3 u = {3.0, 4.0, 0.0};
  vec3 r = v3_normalize(u);
  // A unit vector must have length 1...
  assert(approx_eq(v3_length(r), 1.0));
  // ...and must still point the same direction: (3/5, 4/5, 0)
  assert(approx_eq(r.x, 0.6));
  assert(approx_eq(r.y, 0.8));
  assert(approx_eq(r.z, 0.0));
  printf("test_v3_normalize passed\n");
}

int main(void)
{
  test_v3_add();
  test_v3_sub();
  test_v3_neg();
  test_v3_mul();
  test_v3_dot();
  test_v3_cross();
  test_v3_smul();
  test_v3_sdiv();
  test_v3_length_squared();
  test_v3_length();
  test_v3_normalize();
  printf("All tests passed.\n");
  return 0;
}
