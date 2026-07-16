#pragma once
#include "material.h"
#include "ray.h"
#include "vec3.h"

typedef struct hit_record
{
  point3 p;
  vec3 normal;
  double t;
  _Bool front_face;
  material mat;
} hit_record;

static inline void set_face_normal(hit_record *rec, ray r, vec3 outward_normal)
{
  rec->front_face = v3_dot(r.dir, outward_normal) < 0;
  rec->normal = rec->front_face ? outward_normal : v3_neg(outward_normal);
}
