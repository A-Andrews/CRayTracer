#ifndef HITTABLE_H
#define HITTABLE_H

#include "hit_record.h"
#include "ray.h"
#include "sphere.h"
#include <stdbool.h>

typedef enum { OBJECT_SPHERE } ObjectType;

typedef struct {
  ObjectType type;

  union {
    Sphere sphere;
  };
} Object;

bool hit(const Object *object, Ray r, double ray_tmin, double ray_tmax,
         HitRecord *rec) {
  switch (object->type) {
  case OBJECT_SPHERE:
    return sphere_hit(&object->sphere, r, ray_tmin, ray_tmax, rec);
  }
}

#endif
