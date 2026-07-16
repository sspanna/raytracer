#include "material.h"
#include "hit_record.h"
#include "vec3.h"

_Bool material_scatter(material mat, ray r_in, const struct hit_record *rec,
                       color *attenuation, ray *scattered)
{
  switch (mat.type)
  {
  case MATERIAL_LAMBERTIAN:
  {

    vec3 scatter_direction = v3_add(rec->normal, v3_random_unit_vector());

    if (v3_near_zero(scatter_direction))
    {
      scatter_direction = rec->normal;
    }
    *scattered = (ray){rec->p, scatter_direction};
    *attenuation = mat.lambertian.albedo;
    return 1;
  }
  case MATERIAL_METAL:
  {
    vec3 reflected = v3_reflect(r_in.dir, rec->normal);
    reflected = v3_normalize(reflected);
    reflected =
        v3_add(reflected, v3_smul(v3_random_unit_vector(), mat.metal.fuzz));
    *scattered = (ray){rec->p, reflected};
    *attenuation = mat.metal.albedo;
    return v3_dot(scattered->dir, rec->normal) > 0;
  }
  }

  return 0;
}
