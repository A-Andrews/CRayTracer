#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
  Point3 origin;
  Vec3 direction;
} Ray;

Point3 ray_at(double t, Ray ray) {
  return vec3_element_wise_product(ray.origin, vec3_scale(t, ray.direction));
}

#endif
