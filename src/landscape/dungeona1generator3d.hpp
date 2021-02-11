#ifndef DUNGEONA13D_GENERATOR_H
#define DUNGEONA13D_GENERATOR_H

#include <base/configuration.hpp>
#include "dungeongenerator.hpp"

#define LADDER_FORWARD 1
#define LADDER_BACKWARD 2
#define LADDER_RIGHT 4
#define LADDER_LEFT 8
#define NO_LADDER 0

class DungeonA1Generator3D : public DungeonGenerator {
  void GenerateDungeon(int, int, int, int, int, int);
  std::vector<uint8_t>ladders;

public:
  DungeonA1Generator3D(int);

  void Generate(Location *, size_t, size_t, int, int, int) override;
};

PhysicalObj* create_ladder(glm::vec3, glm::vec3, int, std::string);

#endif
