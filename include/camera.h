#ifndef CAMERA_H
#define CAMERA_H

#include "colour.h"
#include "hit_record.h"
#include "hittable_list.h"
#include "interval.h"
#include "ray.h"
#include "rtweekend.h"
#include "vec3.h"
#include <math.h>

typedef struct {
  double aspect_ratio;
  int image_width;
  int image_height;
  Vec3 pixel_delta_u;
  Vec3 pixel_delta_v;
  Point3 pixel00_loc;
  Point3 camera_centre;
  int samples_per_pixel;
  double pixel_samples_scale;
  int max_depth;
  double vfov;
  Point3 lookfrom;
  Point3 lookat;
  Vec3 vup;
  Vec3 u, v, w;
} Camera;

Colour camera_ray_colour(const Ray r, const HittableList *world, int depth) {
  HitRecord rec;
  if (depth <= 0)
    return (Colour){0, 0, 0};

  if (hit_list(world, r, (Interval){0.001, INFINITY}, &rec)) {
    Ray scattered;
    Colour attenuation;
    if (scatter(&r, &rec, &attenuation, &scattered))
      return vec3_element_wise_product(
          attenuation, camera_ray_colour(scattered, world, depth - 1));
    return (Colour){0, 0, 0};
  }

  Vec3 unit_direction = vec3_unit_vector(r.direction);
  double a = 0.5 * (unit_direction.y + 1.0);
  return vec3_add(vec3_scale((1.0 - a), (Colour){1.0, 1.0, 1.0}),
                  vec3_scale(a, (Colour){0.5, 0.7, 1.0}));
}

Vec3 sample_square(void) {
  return (Vec3){random_double() - 0.5, random_double() - 0.5, 0};
}

Ray camera_get_ray(const Camera *c, int i, int j) {
  // construct a camera ray originating from origin and directed at randomly
  // sampled point
  Vec3 offset = sample_square();
  Point3 pixel_sample = vec3_add(
      c->pixel00_loc, vec3_add(vec3_scale(i + offset.x, c->pixel_delta_u),
                               vec3_scale(j + offset.y, c->pixel_delta_v)));

  Point3 ray_origin = c->camera_centre;
  Vec3 ray_direction = vec3_sub(pixel_sample, ray_origin);

  return (Ray){ray_origin, ray_direction};
}

void camera_render(const Camera *c, const HittableList *world) {
  FILE *file = fopen("image.ppm", "w");

  if (file == NULL) {
    perror("fopen");
    return;
  }

  fprintf(file, "P3\n%d %d\n255\n", c->image_width, c->image_height);

  for (int j = 0; j < c->image_height; j++) {
    for (int i = 0; i < c->image_width; i++) {

      Colour pixel_colour = (Colour){0, 0, 0};
      for (int sample = 0; sample < c->samples_per_pixel; sample++) {
        Ray r = camera_get_ray(c, i, j);
        pixel_colour =
            vec3_add(pixel_colour, camera_ray_colour(r, world, c->max_depth));
      }
      write_colour(file, vec3_scale(c->pixel_samples_scale, pixel_colour));
    }
  }

  fclose(file);
}

Camera camera_initialise(void) {

  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int samples_per_pixel = 100;
  double pixel_samples_scale = 1.0 / samples_per_pixel;
  int max_depth = 10;
  double vfov = 90;

  // Camera positioning
  Point3 lookfrom = (Point3){-2, 2, 1};
  Point3 lookat = (Point3){0, 0, -1};
  Vec3 vup = (Vec3){0, 1, 0};

  // Calculate image height and ensure it isn't less than 1.
  int image_height = (int)(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Camera
  double focal_length = vec3_length(vec3_sub(lookfrom, lookat));
  double theta = degrees_to_radians(vfov);
  double h = tan(theta / 2);
  double viewport_height = 2.0 * h * focal_length;
  double viewport_width =
      viewport_height * ((double)image_width / image_height);
  Vec3 camera_centre = lookfrom;

  Vec3 w = vec3_unit_vector(vec3_sub(lookfrom, lookat));
  Vec3 u = vec3_unit_vector(vec3_cross(vup, w));
  Vec3 v = vec3_cross(w, u);

  // Calculate horizontal and vertical vectors from viewport edges.
  Vec3 viewport_u = vec3_scale(viewport_width, u);
  Vec3 viewport_v = vec3_scale(viewport_height, vec3_neg(v));

  // Calculate delta vectors from pixel to pixel.
  Vec3 pixel_delta_u = vec3_scale(1.0 / image_width, viewport_u);
  Vec3 pixel_delta_v = vec3_scale(1.0 / image_height, viewport_v);

  // Calculate location of upper left pixel.
  Vec3 upper_left_direction = vec3_add(
      vec3_scale(focal_length, w),
      vec3_add(vec3_scale(0.5, viewport_v), vec3_scale(0.5, viewport_u)));
  Point3 viewport_upper_left = vec3_sub(camera_centre, upper_left_direction);
  Point3 pixel00_loc =
      vec3_add(viewport_upper_left,
               vec3_scale(0.5, vec3_add(pixel_delta_u, pixel_delta_v)));

  return (Camera){aspect_ratio,
                  image_width,
                  image_height,
                  pixel_delta_u,
                  pixel_delta_v,
                  pixel00_loc,
                  camera_centre,
                  samples_per_pixel,
                  pixel_samples_scale,
                  max_depth,
                  vfov,
                  lookfrom,
                  lookat,
                  vup,
                  u,
                  v,
                  w};
}

#endif
