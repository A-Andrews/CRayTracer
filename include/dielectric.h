#ifndef DILECTRIC_H
#define DILECTRIC_H

#include <math.h>
typedef struct {
  double refraction_index;
} Dielectric;

double reflectance(double cosine, double refraction_index) {
  double r0 = (1 - refraction_index) / (1 + refraction_index);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}

#endif
