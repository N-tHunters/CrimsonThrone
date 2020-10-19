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

  int GetItemsCount();
  int GetActorsCount();

  void AddItem(Item *);
  void AddActor(Actor *);

  Item * GetItem(int);
  Actor * GetActor(int);

  void DeleteItem(int);
  void DeleteActor(int);

  void Update(float);
  
  void Render(Shader *, Camera *, int, int);
};

#endif
