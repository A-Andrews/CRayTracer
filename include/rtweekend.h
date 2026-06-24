#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <math.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>

const double infinity = INFINITY;
const double pi = 3.1415926535897932385;

static inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

#endif
