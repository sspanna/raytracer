#pragma once
#include "interval.h"
#include "vec3.h"
#include <stdio.h>

typedef vec3 color;

static const interval intensity = (interval){0.000, 0.999};

static inline void write_color(FILE *out, const color pixel_color)
{
  int rbyte = (int)(256 * interval_clamp(intensity, pixel_color.x));
  int gbyte = (int)(256 * interval_clamp(intensity, pixel_color.y));
  int bbyte = (int)(256 * interval_clamp(intensity, pixel_color.z));

  fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}
