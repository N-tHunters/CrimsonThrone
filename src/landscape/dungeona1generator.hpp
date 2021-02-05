#ifndef DUNGEONA1_GENERATOR_H
#define DUNGEONA1_GENERATOR_H

#include "flatgenerator.hpp"

class DungeonA1Generator : public FlatGenerator {
  std::vector<bool> used;
  std::vector<bool> walls;
  void GenerateDungeon(int, int, int, int);
public:
  DungeonA1Generator();
  virtual void Generate(Location *, size_t, size_t, int, int, int);
};

#endif
