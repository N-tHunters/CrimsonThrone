#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#define UP_WALL(x, y) (i * (height * 2 + 1))

#include "flatgenerator.hpp"

class DungeonGenerator : public FlatGenerator {
protected:
  std::vector<bool> used;
  std::vector<bool> walls;
  virtual void GenerateDungeon(int, int, int, int);
  int floors;

  void PrintDungeon(int, int);
public:
  DungeonGenerator(int);
  virtual void Generate(Location *, size_t, size_t, int, int, int);
};

#endif
