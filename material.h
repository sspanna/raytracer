#pragma once
#include "color.h"
#include "ray.h"

struct hit_record; // forward declaration

typedef enum
{
  MATERIAL_LAMBERTIAN,
  MATERIAL_METAL
} material_type;

typedef struct
{
  material_type type;
  union
  {
    struct
    {
      color albedo;
    } lambertian;
    struct
    {
      color albedo;
      double fuzz;
    } metal;
  };
} material;

_Bool material_scatter(material mat, ray r_in, const struct hit_record *rec,
                       color *attenuation, ray *scattered);
