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

class Location;

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
  Location * location;

 public:
  Chunk();
  Chunk(Location *, Terrain *);
  Chunk(Location *, Terrain *, float);

  Terrain * GetTerrain();

  void Draw(ShaderHolder *, Camera *, int, int);
  void DrawWater(ShaderHolder *, Camera *, int, int);

  size_t GetItemsCount();
  size_t GetActorsCount();
  size_t GetObjsCount();
  size_t GetTriggersCount();

  void AddItem(Item *);
  void AddActor(Actor *);
  void AddObj(PhysicalObj *);
  void AddTrigger(BoundaryTrigger *);

  Item * GetItem(size_t);
  Actor * GetActor(size_t);
  PhysicalObj * GetObj(size_t);
  BoundaryTrigger * GetTrigger(size_t);

  void DeleteItemByIndex(size_t);
  void DeleteActorByIndex(size_t);
  void DeleteObjByIndex(size_t);
  void DeleteTriggerByIndex(size_t);
  
  void DeleteItem(Item *);
  void DeleteActor(Actor *);
  void DeleteObj(PhysicalObj *);
  void DeleteTrigger(BoundaryTrigger *);

  void CollideWithAll(PhysicalObj *, float, bool);
  void CollideAll(float);
  void Update(float);

  void CheckAllTriggers(PhysicalObj *);
  void TriggerAll();

  bool IsWaterPresent();
  float GetWaterHeight();
  void SetWaterHeight(float);

  void SetLocation(Location *);
  Location * GetLocation();
};

#endif
