#pragma once

typedef struct
{
  double x;
  double y;
  double z;
} vec3;

typedef vec3 point3;

vec3 v3_add(vec3 u, vec3 v);
vec3 v3_sub(vec3 u, vec3 v);
vec3 v3_neg(vec3 u);

vec3 v3_mul(vec3 u, vec3 v);
double v3_dot(vec3 u, vec3 v);
vec3 v3_cross(vec3 u, vec3 v);

vec3 v3_smul(vec3 u, double c);
vec3 v3_sdiv(vec3 u, double c);

vec3 v3_normalize(vec3 u);
double v3_length(vec3 u);
double v3_length_squared(vec3 u);

void v3_print(vec3 u);

vec3 v3_random();

vec3 v3_random_between(double min, double max);

vec3 v3_random_unit_vector();

vec3 v3_random_on_hemisphere(vec3 normal);
