#pragma once

#include "vec3.h"

typedef struct
{
  point3 orig;
  vec3 dir;
} ray;

static inline vec3 ray_at(ray r, double t)
{
  return v3_add(r.orig, (v3_smul(r.dir, t)));
}
