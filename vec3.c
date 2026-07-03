#include "vec3.h"
#include <math.h>
#include <stdio.h>

vec3 v3_add(vec3 u, vec3 v)
{
  return (vec3){
      .x = u.x + v.x,
      .y = u.y + v.y,
      .z = u.z + v.z,
  };
}

vec3 v3_sub(vec3 u, vec3 v)
{
  return (vec3){
      u.x - v.x,
      u.y - v.y,
      u.z - v.z,
  };
}

vec3 v3_neg(vec3 u)
{
  return (vec3){
      -u.x,
      -u.y,
      -u.z,
  };
}

vec3 v3_mul(vec3 u, vec3 v)
{
  return (vec3){
      u.x * v.x,
      u.y * v.y,
      u.z * v.z,
  };
}

double v3_dot(vec3 u, vec3 v) { return u.x * v.x + u.y * v.y + u.z * v.z; }

vec3 v3_cross(vec3 u, vec3 v)
{
  return (vec3){
      u.y * v.z - u.z * v.y,
      u.z * v.x - u.x * v.z,
      u.x * v.y - u.y * v.x,
  };
}

vec3 v3_smul(vec3 u, double c)
{
  return (vec3){
      u.x * c,
      u.y * c,
      u.z * c,
  };
}

vec3 v3_sdiv(vec3 u, double c) { return v3_smul(u, (1 / c)); }

double v3_length_squared(vec3 u) { return v3_dot(u, u); }

double v3_length(vec3 u) { return sqrt(v3_length_squared(u)); }

vec3 v3_normalize(vec3 u) { return v3_sdiv(u, v3_length(u)); }

void v3_print(vec3 u) { printf("x: %f, y: %f, z: %f\n", u.x, u.y, u.z); }
