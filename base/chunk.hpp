/**
 * \file
 * \brief This file contains declaration of Chunk
 */
#ifndef CHUNK_H
#define CHUNK_H

#include "../physics/terrain.hpp"
#include "../physics/physicalObj.hpp"
#include "../render/shaderHolder.hpp"
#include "boundarytrigger.hpp"
#include "item.hpp"
#include "actor.hpp"
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
  std::vector<BoundaryTrigger *>triggers;
  PhysicalObj* water_obj;

 public:
  Chunk();
  Chunk(Terrain *);
  Chunk(Terrain *, float);

  Terrain * GetTerrain();

  void Draw(ShaderHolder *, Camera *, int, int);
  void DrawWater(ShaderHolder *, Camera *, int, int);

  int GetItemsCount();
  int GetActorsCount();
  int GetObjsCount();
  int GetTriggersCount();

  void AddItem(Item *);
  void AddActor(Actor *);
  void AddObj(PhysicalObj *);
  void AddTrigger(BoundaryTrigger *);

  Item * GetItem(int);
  Actor * GetActor(int);
  PhysicalObj * GetObj(int);
  BoundaryTrigger * GetTrigger(int);

  void DeleteItem(int);
  void DeleteActor(int);
  void DeleteObj(int);
  void DeleteTrigger(int);

  void CollideWithAll(PhysicalObj *, float);
  void CollideAll(float);
  void Update(float);

  void CheckAllTriggers(PhysicalObj *);
  void TriggerAll();

  bool IsWaterPresent();
  float GetWaterHeight();
  void SetWaterHeight(float);
};

#endif
