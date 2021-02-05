#ifndef FLAT_GENERATOR_H
#define FLAT_GENERATOR_H

#include "landscapegenerator.hpp"
#include <vector>

class FlatGenerator : public LandscapeGenerator {
public:
  FlatGenerator();
  virtual void Generate(Location *, size_t, size_t, int, int, int);
};

#endif
