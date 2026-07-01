#ifndef MATERIAL_H
#define MATERIAL_H

#include "matte.h"
#include "metal.h"
#include <stdbool.h>

typedef enum { MATERIAL_LAMBERTIAN, MATERIAL_METAL } MaterialType;

typedef struct {
  MaterialType type;

  union {
    Matte matte;
    Metal metal;
  };
} Material;

#endif
