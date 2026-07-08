#ifndef MATERIAL_H
#define MATERIAL_H

#include "dielectric.h"
#include "matte.h"
#include "metal.h"
#include <stdbool.h>

typedef enum {
  MATERIAL_LAMBERTIAN,
  MATERIAL_METAL,
  MATERIAL_DIELECTRIC
} MaterialType;

typedef struct {
  MaterialType type;

  union {
    Matte matte;
    Metal metal;
    Dielectric dielectric;
  };
} Material;

#endif
