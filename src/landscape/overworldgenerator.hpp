#ifndef OVERWORLD_GENERATOR_H
#define OVERWORLD_GENERATOR_H

#include "landscapegenerator.hpp"
#include <vector>
#include <math.h>
#include <random>

class OverWorldGenerator : public LandscapeGenerator {
public:
  OverWorldGenerator();
  virtual void Generate(Location *, size_t, size_t, int, int, int);
};

#endif
