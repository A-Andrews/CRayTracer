#include "colour.h"
#include "ray.h"
#include "vec3.h"
#include <stdbool.h>
#include <stdio.h>

bool hit_sphere(Point3 centre, double radius, Ray r) {
  Vec3 oc = vec3_sub(centre, r.origin);
  double a = vec3_dot(r.direction, r.direction);
  double b = -2.0 * vec3_dot(r.direction, oc);
  double c = vec3_dot(oc, oc) - radius * radius;
  double descriminant = b * b - 4 * a * c;
  return (descriminant >= 0);
}

Colour ray_colour(Ray r) {
  if (hit_sphere((Point3){0, 0, -1}, 0.5, r))
    return (Colour){1, 0, 0};
  Vec3 unit_direction = vec3_unit_vector(r.direction);
  double a = 0.5 * (unit_direction.y + 1.0);
  return vec3_add(vec3_scale(1.0 - a, (Colour){1.0, 1.0, 1.0}),
                  vec3_scale(a, (Colour){0.5, 0.7, 1.0}));
}

int main(void) {
  // Image

  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;

  // Calculate image height and ensure it isn't less than 1.
  int image_height = (int)image_width / aspect_ratio;
  image_height = (image_height < 1) ? 1 : image_height;

  // Camera
  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * ((double)image_width / image_height);
  Vec3 camera_centre = (Point3){0, 0, 0};

  // Calculate horizontal and vertical vectors from viewport edges.
  Vec3 viewport_u = (Vec3){viewport_width, 0, 0};
  Vec3 viewport_v = (Vec3){0, -viewport_height, 0};

  // Calculate delta vectors from pixel to pixel.
  Vec3 pixel_delta_u = vec3_scale(1.0 / image_width, viewport_u);
  Vec3 pixel_delta_v = vec3_scale(1.0 / image_height, viewport_v);

  // Calculate location of upper left pixel.

  Vec3 uppel_left_direction = vec3_add(
      (Vec3){0, 0, focal_length},
      vec3_add(vec3_scale(0.5, viewport_v), vec3_scale(0.5, viewport_u)));
  Point3 viewport_upper_left = vec3_sub(camera_centre, uppel_left_direction);
  Point3 pixel00_loc =
      vec3_add(viewport_upper_left,
               vec3_scale(0.5, vec3_add(pixel_delta_u, pixel_delta_v)));

  // Render

  FILE *file = fopen("image.ppm", "w");

  if (file == NULL) {
    perror("fopen");
    return 1;
  }

  fprintf(file, "P3\n%d %d\n255\n", image_width, image_height);

  for (int j = 0; j < image_height; j++) {
    printf("Lines remaining: %d\n", image_height - j);
    for (int i = 0; i < image_width; i++) {

      Vec3 pixel_adjustment =
          vec3_add(vec3_scale(i, pixel_delta_u), vec3_scale(j, pixel_delta_v));
      Point3 pixel_centre = vec3_add(pixel00_loc, pixel_adjustment);
      Vec3 ray_direction = vec3_sub(pixel_centre, camera_centre);
      Ray ray = (Ray){camera_centre, ray_direction};
      Colour pixel_colour = ray_colour(ray);
      write_colour(file, pixel_colour);
    }
  }

  printf("Hello World!\n");
  fclose(file);
  return 0;
}
