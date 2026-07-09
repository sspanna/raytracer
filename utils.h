#include <stdlib.h>

static inline double random_double() { return rand() / (RAND_MAX + 1.0); }

static inline double random_double_between(double min, double max)
{
  return min + (max - min) * random_double();
}
