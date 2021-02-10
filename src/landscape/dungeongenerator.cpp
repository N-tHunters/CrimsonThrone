#include "dungeongenerator.hpp"

DungeonGenerator::DungeonGenerator(int floors) : floors(floors) {}


void DungeonGenerator::PrintDungeon(int height, int width) {
  int q = 0;
  for (int i = 0; i < height * 2 + 1; i++) {
    if (i % 2 == 0) {
      printf("#");
      for (int j = 0; j < width; j++) {
        if (walls[q++])
          printf("##");
        else
          printf(" #");
      }
    } else {
      for (int j = 0; j < width + 1; j++) {
        if (walls[q++])
          printf("# ");
        else
          printf("  ");
      }
    }
    puts("");
  }
}

void DungeonGenerator::Generate(Location *, size_t, size_t, int, int, int) {}

void DungeonGenerator::GenerateDungeon(int, int, int, int) {
  
}
