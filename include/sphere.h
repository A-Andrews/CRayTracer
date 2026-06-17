#ifndef SPHERE_H
#define SPHERE_H

#include "hit_record.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>
#include <stdbool.h>

typedef struct {
  Point3 centre;
  double radius;
} Sphere;

bool sphere_hit(const Sphere *s, Ray r, double ray_tmin, double ray_tmax,
                HitRecord *rec) {

  Vec3 oc = vec3_sub(s->centre, r.origin);
  double a = pow(vec3_length(r.direction), 2);
  double h = vec3_dot(r.direction, oc);
  double c = pow(vec3_length(oc), 2) - s->radius * s->radius;
  double discriminant = h * h - a * c;

  if (discriminant < 0) {
    return false;
  }

  double sqrtd = sqrt(discriminant);

  // find nearest root in range

  double root = (h - sqrtd) / a;
  if (root <= ray_tmin || ray_tmax <= root) {
    root = (h + sqrtd) / a;
    if (root <= ray_tmin || ray_tmax <= root)
      return false;
  }

  rec->t = root;
  rec->p = ray_at(rec->t, r);
  Vec3 outward_normal = vec3_scale(1 / s->radius, vec3_sub(rec->p, s->centre));
  set_face_normal(rec, r, outward_normal);

  return true;
}

#endif
