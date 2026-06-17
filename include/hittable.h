#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "vec3.h"
#include <stdbool.h>

typedef struct {
  Point3 p;
  Vec3 normal;
  double t;
  bool front_face;
} HitRecord;

bool hit(Ray r, double ray_tmin, double ray_tmax, HitRecord *rec);

void set_face_normal(HitRecord *rec, Ray r, Vec3 outward_normal) {
  // set the hit record normal vector
  // outward_normal is assumed to have unit length

  rec->front_face = vec3_dot(r.direction, outward_normal) < 0;
  rec->normal = rec->front_face ? outward_normal : vec3_neg(outward_normal);
}

#endif
