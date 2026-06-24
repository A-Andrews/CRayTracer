#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "vec3.h"
#include <stdbool.h>
#include <stdio.h>

int main(void) {

  // World
  HittableList world = (HittableList){0};

  hittable_list_add_sphere(&world, (Sphere){(Point3){0, 0, -1}, 0.5});
  hittable_list_add_sphere(&world, (Sphere){(Point3){0, -100.5, -1}, 100});

  Camera camera = camera_initialise();
  camera_render(&camera, &world);

  return 0;
}
