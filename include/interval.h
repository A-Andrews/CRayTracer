#ifndef INTERVAL_H
#define INTERVAL_H

#include <math.h>
#include <stdbool.h>
typedef struct {
  double min;
  double max;
} Interval;

Interval interval_new(void) { return (Interval){INFINITY, -INFINITY}; }

double interval_size(const Interval i) { return i.max - i.min; }

bool interval_contains(const Interval i, double x) {
  return i.min <= x && x <= i.max;
}

bool interval_surrounds(const Interval i, double x) {
  return i.min < x && x < i.max;
}

const Interval interval_empty = (Interval){INFINITY, -INFINITY};
const Interval interval_universe = (Interval){-INFINITY, INFINITY};
#endif
