#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <math.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const double infinity = INFINITY;
const double pi = 3.1415926535897932385;

static inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

static inline double random_double(void) { return rand() / (RAND_MAX + 1.0); }

static inline double random_double_interval(double min, double max) {
  return min + (max - min) * random_double();
}

#endif
