#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#define UP_WALL(X, Y) ((X) * (height * 2 + 1) + (Y))
#define DOWN_WALL(X, Y) (((X) + 1) * (height * 2 + 1) + (Y))
#define RIGHT_WALL(X, Y) (height + (height * 2 + 1) * (X) + (Y))
#define LEFT_WALL(X, Y) (height + (height * 2 + 1) * (X) + ((Y) + 1))


#define FLOOR_3D_I(Z) \
  ((Z) * (height + (height * 2 + 1) * width + width * height))
#define UP_WALL_3D(X, Y, Z) \
  (FLOOR_3D_I((Z)) + UP_WALL((X), (Y)))
#define DOWN_WALL_3D(X, Y, Z) \
  (FLOOR_3D_I((Z)) + DOWN_WALL((X), (Y)))
#define RIGHT_WALL_3D(X, Y, Z) \
  (FLOOR_3D_I((Z)) + RIGHT_WALL((X), (Y)))
#define LEFT_WALL_3D(X, Y, Z) \
  (FLOOR_3D_I((Z)) + LEFT_WALL((X), (Y)))
#define ROOF_3D(X, Y, Z) \
  (FLOOR_3D_I(((Z) + 1)) - width * height + (Y) * width + (X))
#define FLOOR_3D(X, Y, Z) \
  (ROOF_3D((X),(Y),((Z) - 1)))


#include "flatgenerator.hpp"

class DungeonGenerator : public FlatGenerator {
protected:
  std::vector<bool> used;
  std::vector<bool> walls;
  virtual void GenerateDungeon(int, int, int, int);
  size_t floors;

  void PrintDungeon(int, int);
  void PrintDungeon3D(int, int, int);
public:
  DungeonGenerator(size_t);
  virtual void Generate(Location *, size_t, size_t, int, int, int);
};

#endif
