#include "colour.h"
#include "ray.h"
#include "vec3.h"
#include <stdio.h>

Colour ray_colour(Ray r) { return (Colour){0, 0, 0}; }

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
  double viewport_width = viewport_height * (double)image_width / image_height;
  Vec3 camera_centre = (Point3){0, 0, 0};

  // Calculate horizontal and vertical vectors from viewport edges.
  Vec3 viewport_u = (Vec3){viewport_width, 0, 0};
  Vec3 viewport_v = (Vec3){0, -image_height, 0};

  // Calculate delta vectors from pixel to pixel.
  Vec3 pixel_delta_u = vec3_scale(1.0 / image_width, viewport_u);
  Vec3 pixel_delta_v = vec3_scale(1.0 / image_height, viewport_v);

  // Calculate location of upper left pixel.
  Point3 viewport_upper_left = vec3_sub(
      camera_centre, vec3_add((Vec3){0, 0, focal_length},
                              vec3_add(vec3_scale(1.0 / 2.0, viewport_v),
                                       vec3_scale(1.0 / 2.0, viewport_u))));
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

      Colour pixel_colour = (Colour){(double)i / (image_width - 1),
                                     (double)j / (image_height - 1), 0.0};
      write_colour(file, pixel_colour);
    }
  }

  printf("Hello World!\n");
  fclose(file);
  return 0;
}
