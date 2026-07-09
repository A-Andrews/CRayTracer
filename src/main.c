#include "camera.h"
#include "colour.h"
#include "dielectric.h"
#include "hittable_list.h"
#include "material.h"
#include "matte.h"
#include "metal.h"
#include "rtweekend.h"
#include "sphere.h"
#include "vec3.h"
#include <stdbool.h>
#include <stdio.h>

int main(void) {

  // World
  HittableList world = (HittableList){0};
  //
  // hittable_list_add_sphere(
  //     &world, (Sphere){(Point3){0, 0, -1.2}, 0.5,
  //                      (Material){.type = MATERIAL_LAMBERTIAN,
  //                                 .matte = (Matte){(Colour){0.8, 0.8,
  //                                 0.0}}}});
  // hittable_list_add_sphere(
  //     &world, (Sphere){(Point3){0, -100.5, -1}, 100,
  //                      (Material){.type = MATERIAL_LAMBERTIAN,
  //                                 .matte = (Matte){(Colour){0.1, 0.2,
  //                                 0.5}}}});
  // hittable_list_add_sphere(
  //     &world, (Sphere){(Point3){-1.0, 0.0, -1.0}, 0.5,
  //                      (Material){.type = MATERIAL_DIELECTRIC,
  //                                 .dielectric = (Dielectric){1.50}}});
  // hittable_list_add_sphere(
  //     &world, (Sphere){(Point3){-1.0, 0.0, -1.0}, 0.4,
  //                      (Material){.type = MATERIAL_DIELECTRIC,
  //                                 .dielectric = (Dielectric){1.00 / 1.50}}});
  // hittable_list_add_sphere(
  //     &world,
  //     (Sphere){(Point3){1.0, 0.0, -1.0}, 0.5,
  //              (Material){.type = MATERIAL_METAL,
  //                         .metal = (Metal){(Colour){0.8, 0.6, 0.2}, 1.0}}});

  Material ground_material = (Material){
      .type = MATERIAL_LAMBERTIAN, .matte = (Matte){(Colour){0.5, 0.5, 0.5}}};

  hittable_list_add_sphere(
      &world, (Sphere){(Point3){0, -1000, 0}, 1000, ground_material});

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      double choose_mat = random_double();
      Point3 centre =
          (Point3){a + 0.9 * random_double(), 0.2, b + 0.9 * random_double()};

      if (vec3_length(vec3_sub(centre, (Point3){4, 0.2, 0})) > 0.9) {
        Material sphere_material;

        if (choose_mat < 0.8) {
          Colour albedo = vec3_element_wise_product(
              (Colour){random_double(), random_double(), random_double()},
              (Colour){random_double(), random_double(), random_double()});
          sphere_material =
              (Material){.type = MATERIAL_LAMBERTIAN, .matte = (Matte){albedo}};
          hittable_list_add_sphere(&world,
                                   (Sphere){centre, 0.2, sphere_material});
        } else if (choose_mat < 0.95) {
          Colour albedo = (Colour){random_double_interval(0.5, 1),
                                   random_double_interval(0.5, 1),
                                   random_double_interval(0.5, 1)};
          double fuzz = random_double();
          sphere_material = (Material){.type = MATERIAL_METAL,
                                       .metal = (Metal){albedo, fuzz}};
          hittable_list_add_sphere(&world,
                                   (Sphere){centre, 0.2, sphere_material});
        } else {
          sphere_material = (Material){.type = MATERIAL_DIELECTRIC,
                                       .dielectric = (Dielectric){1.5}};
          hittable_list_add_sphere(&world,
                                   (Sphere){centre, 0.2, sphere_material});
        }
      }
    }
  }

  Material material1 =
      (Material){.type = MATERIAL_DIELECTRIC, .dielectric = (Dielectric){1.5}};
  hittable_list_add_sphere(&world, (Sphere){(Point3){0, 1, 0}, 1.0, material1});

  Material material2 = (Material){.type = MATERIAL_LAMBERTIAN,
                                  .matte = (Matte){(Colour){0.4, 0.2, 0.1}}};
  hittable_list_add_sphere(&world,
                           (Sphere){(Point3){-4, 1, 0}, 1.0, material2});

  Material material3 = (Material){
      .type = MATERIAL_METAL, .metal = (Metal){(Colour){0.7, 0.6, 0.5}, 0.0}};
  hittable_list_add_sphere(&world, (Sphere){(Point3){4, 1, 0}, 1.0, material3});

  Camera camera = camera_initialise();
  camera.lookfrom = (Point3){-2, 2, 1};
  camera.lookat = (Point3){0, 0, -1};
  camera.vup = (Vec3){0, 1, 0};
  camera_render(&camera, &world);

  return 0;
}
