#pragma once
#include "vec3.h"
#include <stdio.h>

typedef vec3 color;

static inline void write_color(FILE *out, const color pixel_color)
{
  int rbyte = (int)(255.999 * pixel_color.x);
  int gbyte = (int)(255.999 * pixel_color.y);
  int bbyte = (int)(255.999 * pixel_color.z);

  fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}
