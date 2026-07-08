#include "vec3.h"
#include "rtweekend.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

Vec3 vec3_add(Vec3 a, Vec3 b) {
  return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 vec3_neg(Vec3 a) { return (Vec3){-a.x, -a.y, -a.z}; }

Vec3 vec3_sub(Vec3 a, Vec3 b) {
  return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}
Vec3 vec3_scale(double i, Vec3 a) { return (Vec3){i * a.x, i * a.y, i * a.z}; }

Vec3 vec3_element_wise_product(Vec3 a, Vec3 b) {
  return (Vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

double vec3_dot(Vec3 a, Vec3 b) {
  return (double){a.x * b.x + a.y * b.y + a.z * b.z};
}

Vec3 vec3_cross(Vec3 a, Vec3 b) {
  return (Vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x};
}

Vec3 vec3_unit_vector(Vec3 a) {
  return vec3_scale((double)1 / vec3_length(a), a);
}

double vec3_length(Vec3 a) { return sqrt(vec3_dot(a, a)); }

void vec3_write(FILE *file, Vec3 a) {
  fprintf(file, "%i %i %i\n", (int)a.x, (int)a.y, (int)a.z);
}

Vec3 vec3_random(void) {
  return (Vec3){random_double(), random_double(), random_double()};
}

Vec3 vec3_random_limit(double min, double max) {
  return (Vec3){random_double_interval(min, max),
                random_double_interval(min, max),
                random_double_interval(min, max)};
}

Vec3 vec3_random_unit_vector(void) {
  while (true) {
    Vec3 p = vec3_random_limit(-1, 1);
    double lensq = pow(vec3_length(p), 2);
    if (1e-160 < lensq && lensq <= 1)
      return vec3_scale(1 / sqrt(lensq), p);
  }
}

Vec3 vec3_random_on_hemisphere(const Vec3 normal) {
  Vec3 on_unit_sphere = vec3_random_unit_vector();
  if (vec3_dot(on_unit_sphere, normal) > 0.0)
    return on_unit_sphere;
  else
    return vec3_neg(on_unit_sphere);
}

bool vec3_near_zero(const Vec3 a) {
  double s = 1e-8;
  return (fabs(a.x) < s) && (fabs(a.y) < s) && (fabs(a.z) < s);
}

Vec3 vec3_reflect(const Vec3 a, const Vec3 n) {
  return vec3_sub(a, vec3_scale(2 * vec3_dot(a, n), n));
}

Vec3 vec3_refract(const Vec3 *uv, const Vec3 *n, double etai_over_etat) {
  double cos_theta = fmin(vec3_dot(vec3_neg(*uv), *n), 1.0);
  Vec3 r_out_perp =
      vec3_scale(etai_over_etat, vec3_add(*uv, vec3_scale(cos_theta, *n)));
  Vec3 r_out_parallel =
      vec3_scale(-sqrt(fabs(1.0 - pow(vec3_length(r_out_perp), 2))), *n);
  return vec3_add(r_out_perp, r_out_parallel);
}

Vec3 vec3_random_in_unit_disk(void) {
  while (true) {
    Vec3 p =
        (Vec3){random_double_interval(-1, 1), random_double_interval(-1, 1), 0};
    if (pow(vec3_length(p), 2) < 1)
      return p;
  }
}
