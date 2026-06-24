#ifndef COLOUR_H
#define COLOUR_H

#include "interval.h"
#include "vec3.h"

#include <stdio.h>

typedef Vec3 Colour;

void write_colour(FILE *file, const Colour pixel_colour) {
  double r = pixel_colour.x;
  double g = pixel_colour.y;
  double b = pixel_colour.z;

  // Translate the [0,1] component values to the byte range [0,255].
  static const Interval intensity = (Interval){0.000, 0.999};
  int rbyte = (int)255.999 * interval_clamp(intensity, r);
  int gbyte = (int)255.999 * interval_clamp(intensity, g);
  int bbyte = (int)255.999 * interval_clamp(intensity, b);

  // Write out the pixel colour components.
  fprintf(file, "%i %i %i\n", rbyte, gbyte, bbyte);
}

#endif
