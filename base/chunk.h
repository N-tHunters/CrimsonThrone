/**
 * \file
 * \brief This file contains declaration of Chunk
 */
#ifndef CHUNK_H
#define CHUNK_H

#include "../physics/terrain.h"
#include "../physics/physicalObj.h"
#include "../render/shaderHolder.h"
#include "item.h"
#include "actor.h"
#include <vector>

/**
 * \brief Chunk is a piece of location for optiming rendering and processing.
 * Chunks are heavily used to interact with player with enviroment. \warning Consider that player is not part of chunk, it's separate object.
 */
class Chunk {
 private:
  bool is_water_present;
  float water_height;
  Terrain * terrain;
  std::vector<Item *>items;
  std::vector<Actor *>actors;
  std::vector<PhysicalObj *>objects;
  PhysicalObj* water_obj;

 public:
  Chunk();
  Chunk(Terrain *);
  Chunk(Terrain *, float);

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

  bool IsWaterPresent();
  float GetWaterHeight();
  void SetWaterHeight(float);
};

#endif
