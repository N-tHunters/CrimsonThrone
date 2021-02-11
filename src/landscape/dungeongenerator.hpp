#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#define UP_WALL(X, Y) ((X) * (height * 2 + 1) + (Y))
#define DOWN_WALL(X, Y) (((X) + 1) * (height * 2 + 1) + (Y))
#define RIGHT_WALL(X, Y) (height + (height * 2 + 1) * (X) + (Y))
#define LEFT_WALL(X, Y) (height + (height * 2 + 1) * (X) + ((Y) + 1))

#include "flatgenerator.hpp"

class DungeonGenerator : public FlatGenerator {
protected:
  std::vector<bool> used;
  std::vector<bool> walls;
  virtual void GenerateDungeon(int, int, int, int);
  int floors;

  void PrintDungeon(int, int);
  void PrintDungeon3D(int, int);
public:
  DungeonGenerator(int);
  virtual void Generate(Location *, size_t, size_t, int, int, int);
};

#endif
