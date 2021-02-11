#ifndef DUNGEONA13D_GENERATOR_H
#define DUNGEONA13D_GENERATOR_H

#include <base/configuration.hpp>
#include "dungeongenerator.hpp"

class DungeonA1Generator3D : public DungeonGenerator {
  void GenerateDungeon(int, int, int, int, int, int);

public:
  DungeonA1Generator3D(int);

  void Generate(Location *, size_t, size_t, int, int, int) override;
};

#endif
