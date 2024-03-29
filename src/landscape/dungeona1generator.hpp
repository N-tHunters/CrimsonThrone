#ifndef DUNGEONA1_GENERATOR_H
#define DUNGEONA1_GENERATOR_H

#include <base/configuration.hpp>
#include "dungeongenerator.hpp"

class DungeonA1Generator : public DungeonGenerator {
  void GenerateDungeon(int, int, int, int) override;

public:
  DungeonA1Generator();

  void Generate(Location *, size_t, size_t, int, int, int) override;
};

#endif
