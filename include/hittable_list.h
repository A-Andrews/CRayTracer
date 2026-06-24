#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "interval.h"

#include <memory.h>

#define MAX_OBJECTS 128

typedef struct {
  int count;
  Object objects[MAX_OBJECTS];
} HittableList;

void hittable_list_add_sphere(HittableList *list, const Sphere sphere) {
  if (list->count >= MAX_OBJECTS)
    return;

  list->objects[list->count++] =
      (Object){.type = OBJECT_SPHERE, .sphere = sphere};
}

bool hit_list(HittableList *list, Ray r, Interval ray_t, HitRecord *rec) {
  HitRecord temp_rec;
  bool hit_anything = false;
  double closest_so_far = ray_t.max;

  for (int i = 0; i < list->count; i++) {
    if (hit(&list->objects[i], r, (Interval){ray_t.min, closest_so_far},
            &temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      *rec = temp_rec;
    }
  }
  return hit_anything;
}

#endif
