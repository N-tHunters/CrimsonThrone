#ifndef CHUNK_H
#define CHUNK_H

#include "../physics/terrain.h"
#include "../render/shaderHolder.h"
#include "item.h"
#include "actor.h"
#include <vector>

class Chunk {
 private:
  Terrain * terrain;
  std::vector<Item *>items;
  std::vector<Actor *>actors;
  std::vector<PhysicalObj *>objects;

 public:
  Chunk();
  Chunk(Terrain *);

  Terrain * GetTerrain();

  void Draw(ShaderHolder *, Camera *, int, int);

  int GetItemsCount();
  int GetActorsCount();
  int GetObjectsCount();

  void AddItem(Item *);
  void AddActor(Actor *);
  void AddObject(PhysicalObj *);

  Item * GetItem(int);
  Actor * GetActor(int);
  PhysicalObj * GetObject(int);

  void DeleteItem(int);
  void DeleteActor(int);
  void DeleteObject(int);

  void Update(float);
};

#endif
