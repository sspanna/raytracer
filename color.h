#pragma once
#include "interval.h"
#include "vec3.h"
#include <math.h>
#include <stdio.h>

typedef vec3 color;

static const interval intensity = (interval){0.000, 0.999};

static inline double linear_to_gamma(double linear)
{
  if (linear > 0)
  {
    return sqrt(linear);
  }
  return 0;
}
static inline void write_color(FILE *out, const color pixel_color)
{
  double r = linear_to_gamma(pixel_color.x);
  double g = linear_to_gamma(pixel_color.y);
  double b = linear_to_gamma(pixel_color.z);

  int rbyte = (int)(256 * interval_clamp(intensity, r));
  int gbyte = (int)(256 * interval_clamp(intensity, g));
  int bbyte = (int)(256 * interval_clamp(intensity, b));

  fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}
