#ifndef HITRECORD_H
#define HITRECORD_H

#include "colour.h"
#include "dielectric.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"
#include <math.h>
#include <stdbool.h>

typedef struct {
  Point3 p;
  Vec3 normal;
  double t;
  bool front_face;
  Material material;
} HitRecord;

bool scatter_lambertian(const HitRecord *rec, Colour *attenuation,
                        Ray *scattered, Matte m) {
  Vec3 scatter_direction = vec3_add(rec->normal, vec3_random_unit_vector());

  if (vec3_near_zero(scatter_direction))
    scatter_direction = rec->normal;

  *scattered = ((Ray){rec->p, scatter_direction});
  *attenuation = m.albedo;
  return true;
}

bool scatter_metal(const Ray *r_in, const HitRecord *rec, Colour *attenuation,
                   Ray *scattered, Metal m) {
  Vec3 reflected = vec3_reflect(r_in->direction, rec->normal);
  reflected = vec3_add(vec3_unit_vector(reflected),
                       vec3_scale(m.fuzz, vec3_random_unit_vector()));
  *scattered = ((Ray){rec->p, reflected});
  *attenuation = m.albedo;
  return (vec3_dot(scattered->direction, rec->normal) > 0);
}

bool scatter_dielectric(const Ray *r_in, const HitRecord *rec,
                        Colour *attenuation, Ray *scattered, Dielectric d) {
  *attenuation = (Colour){1.0, 1.0, 1.0};
  double ri = rec->front_face ? (1.0 / d.refraction_index) : d.refraction_index;

  Vec3 unit_direction = vec3_unit_vector(r_in->direction);
  double cos_theta = fmin(vec3_dot(vec3_neg(unit_direction), rec->normal), 1.0);
  double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

  bool cannot_refract = ri * sin_theta > 1.0;
  Vec3 direction;

  if (cannot_refract)
    direction = vec3_reflect(unit_direction, rec->normal);
  else
    direction = vec3_refract(&unit_direction, &rec->normal, ri);

  *scattered = (Ray){rec->p, direction};
  return true;
}

bool scatter(const Ray *r_in, const HitRecord *rec, Colour *attenuation,
             Ray *scattered) {
  switch (rec->material.type) {
  case MATERIAL_LAMBERTIAN:
    return scatter_lambertian(rec, attenuation, scattered, rec->material.matte);
  case MATERIAL_METAL:
    return scatter_metal(r_in, rec, attenuation, scattered,
                         rec->material.metal);
  case MATERIAL_DIELECTRIC:
    return scatter_dielectric(r_in, rec, attenuation, scattered,
                              rec->material.dielectric);
  }
  return false;
}

void set_face_normal(HitRecord *rec, Ray r, Vec3 outward_normal) {
  // set the hit record normal vector
  // outward_normal is assumed to have unit length

  rec->front_face = vec3_dot(r.direction, outward_normal) < 0;
  rec->normal = rec->front_face ? outward_normal : vec3_neg(outward_normal);
}
#endif
