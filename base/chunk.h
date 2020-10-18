#ifndef CHUNK_H
#define CHUNK_H

#include "../physics/terrain.h"
#include "item.h"
#include "actor.h"
#include <vector>

class Chunk {
 private:
  Terrain * terrain;
  std::vector<Item *>items;
  std::vector<Actor *>actors;

 public:
  Chunk();
  Chunk(Terrain *);

  void Render();
};

#endif
