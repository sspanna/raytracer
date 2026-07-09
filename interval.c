#include "interval.h"
#include <math.h>

double interval_size(interval itv) { return itv.max - itv.min; }

_Bool interval_contains(interval itv, double x)
{
  return itv.min <= x && x <= itv.max;
}

_Bool interval_surrounds(interval itv, double x)
{
  return itv.min < x && x < itv.max;
}

double interval_clamp(interval itv, double x)
{
  if (x < itv.min)
    return itv.min;
  if (x > itv.max)
    return itv.max;
  return x;
}

const interval interval_empty = (interval){INFINITY, -INFINITY};
const interval interval_universe = (interval){-INFINITY, INFINITY};
