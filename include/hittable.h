#ifndef HITTABLE_H
#define HITTABLE_H

#include "hit_record.h"
#include "interval.h"
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

bool hit(const Object *object, Ray r, Interval ray_t, HitRecord *rec) {
  switch (object->type) {
  case OBJECT_SPHERE:
    return sphere_hit(&object->sphere, r, ray_t, rec);
  }
}

#endif
