#pragma once

#include "hit_record.h"
#include "ray.h"
#include "vec3.h"

typedef struct
{
  point3 center;
  double radius;
} sphere;

_Bool sphere_hit(sphere s, ray r, double ray_tmin, double ray_tmax,
                 hit_record *rec);
