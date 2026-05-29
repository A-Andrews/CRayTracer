#include "vec3.h"
#include <math.h>

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
  return (Vec3){a.y * b.z - a.z * b.y, a.x * b.z - a.z * b.x,
                a.x * b.y - a.y * b.x};
}

Vec3 vec3_unit_vector(Vec3 a) {
  return vec3_scale((double)1 / vec3_length(a), a);
}

double vec3_length(Vec3 a) { return sqrt(vec3_dot(a, a)); }
