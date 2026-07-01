#include "camera.h"
#include "colour.h"
#include "hittable_list.h"
#include "material.h"
#include "matte.h"
#include "metal.h"
#include "sphere.h"
#include "vec3.h"
#include <stdbool.h>
#include <stdio.h>

int main(void) {

  // World
  HittableList world = (HittableList){0};

  hittable_list_add_sphere(
      &world, (Sphere){(Point3){0, 0, -1}, 0.5,
                       (Material){.type = MATERIAL_LAMBERTIAN,
                                  .matte = (Matte){(Colour){0.8, 0.8, 0.0}}}});
  hittable_list_add_sphere(
      &world, (Sphere){(Point3){0, -100.5, -1}, 100,
                       (Material){.type = MATERIAL_LAMBERTIAN,
                                  .matte = (Matte){(Colour){0.1, 0.2, 0.5}}}});
  hittable_list_add_sphere(
      &world, (Sphere){(Point3){-1.0, 0.0, -1.0}, 0.5,
                       (Material){.type = MATERIAL_METAL,
                                  .metal = (Metal){(Colour){0.8, 0.8, 0.8}}}});
  hittable_list_add_sphere(
      &world, (Sphere){(Point3){1.0, 0.0, -1.0}, 0.5,
                       (Material){.type = MATERIAL_METAL,
                                  .metal = (Metal){(Colour){0.8, 0.6, 0.2}}}});

  Camera camera = camera_initialise();
  camera_render(&camera, &world);

  return 0;
}
