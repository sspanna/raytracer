#pragma once

typedef struct
{
  double min;
  double max;
} interval;

double interval_size(interval itv);

_Bool interval_contains(interval itv, double x);

_Bool interval_surrounds(interval itv, double x);

extern const interval interval_empty;
extern const interval interval_universe;
