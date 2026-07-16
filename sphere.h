#pragma once

#include "hit_record.h"
#include "interval.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"

typedef struct
{
  point3 center;
  double radius;
  material mat;
} sphere;

_Bool sphere_hit(sphere s, ray r, interval ray_t, hit_record *rec);
