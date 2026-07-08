#include "sphere.h"
#include "hit_record.h"
#include "interval.h"
#include "vec3.h"
#include <math.h>

_Bool sphere_hit(sphere s, ray r, interval ray_t, hit_record *rec)
{

  vec3 oc = v3_sub(s.center, r.orig);
  double a = v3_dot(r.dir, r.dir);
  double h = v3_dot(r.dir, oc);
  double c = v3_dot(oc, oc) - s.radius * s.radius;
  double discriminant = h * h - a * c;
  if (discriminant < 0)
  {
    return 0;
  }
  double sqrtd = sqrt(discriminant);

  double root = (h - sqrtd) / a;
  if (!interval_surrounds(ray_t, root))
  {
    root = (h + sqrtd) / a;
    if (!interval_surrounds(ray_t, root))
    {
      return 0;
    }
  }

  rec->t = root;
  rec->p = ray_at(r, root);
  vec3 outward_normal = v3_sdiv(v3_sub(rec->p, s.center), s.radius);
  set_face_normal(rec, r, outward_normal);

  return 1;
}
