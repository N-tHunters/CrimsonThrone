#ifndef LANDSCAPEGENERATOR_H
#define LANDSCAPEGENERATOR_H

#include <stddef.h>

class Location;

class LandscapeGenerator {
public:
  LandscapeGenerator();
  virtual void Generate(Location *, size_t, size_t, int, int, int);
};

#endif
