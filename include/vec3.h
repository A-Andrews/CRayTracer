#ifndef VEC3_H
#define VEC3_H

#include <stdio.h>

typedef struct {
  float x;
  float y;
  float z;
} Vec3;

Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_neg(Vec3);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_scale(double i, Vec3 a);
Vec3 vec3_element_wise_product(Vec3 a, Vec3 b);
double vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);
Vec3 vec3_unit_vector(Vec3 a);
double vec3_length(Vec3 a);

#endif
