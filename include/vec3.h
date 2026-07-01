#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  double x, y, z;
} Vec3;

typedef Vec3 Point3;

Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_neg(Vec3);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_scale(double i, Vec3 a);
Vec3 vec3_element_wise_product(Vec3 a, Vec3 b);
double vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);
Vec3 vec3_unit_vector(Vec3 a);
double vec3_length(Vec3 a);
void vec3_write(FILE *file, Vec3 a);
Vec3 vec3_random(void);
Vec3 vec3_random_limit(double min, double max);
Vec3 vec3_random_unit_vector(void);
Vec3 vec3_random_on_hemisphere(const Vec3 normal);
bool vec3_near_zero(const Vec3 a);
Vec3 vec3_reflect(const Vec3 a, const Vec3 n);

#endif
