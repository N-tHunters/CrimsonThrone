/**
 * \file
 * \brief This file contains implementation of Chunk
 */
#include "chunk.h"

/// Maximum velocity
#define VCAP 0.1f

/***
 * Empty constructor
 * \warning Should not use
 */
Chunk::Chunk() {}

/**
 * Basic constructor
 * \param terrain Landscape of this chunk
 */
Chunk::Chunk(Terrain * terrain) {
  this->terrain = terrain;
}

/**
 * Get terrain
 * \return Landsacpe of this chunk
 */
Terrain * Chunk::GetTerrain() {
  return this->terrain;
}

/**
 * Draw everything in this chunk - terrain, actors, items and objects
 * \param shaderHolder Shader set used to render
 * \param camera Point of view
 * \param width Width of the screen
 * \param height Height of the screen
 */
void Chunk::Draw(ShaderHolder * shaderHolder, Camera * camera, int width, int height) {
  this->terrain->draw(shaderHolder, camera, width, height);
  for(int i = 0; i <  this->GetObjectsCount(); i ++) {
    this->objects[i]->draw(shaderHolder, camera, width, height);
  }
  for(int i = 0; i <  this->GetActorsCount(); i ++) {
    this->actors[i]->GetPhysicalObj()->draw(shaderHolder, camera, width, height);
  }
  for(int i = 0; i <  this->GetItemsCount(); i ++) {
    this->items[i]->GetPhysicalObj()->draw(shaderHolder, camera, width, height);
  }
}

/**
 * Get number of items in this chunk
 * \return Number of items
 */
int Chunk::GetItemsCount() {
  return this->items.size();
}

/**
 * Get number of actors in this chunk
 * \return Number of actors
 */
int Chunk::GetActorsCount() {
  return this->actors.size();
}

/**
 * Get number of objects in this chunk
 * \return Number of objects
 */
int Chunk::GetObjectsCount() {
  return this->objects.size();
}

/**
 * Add item to chunk
 * \param item Item to add
 */
void Chunk::AddItem(Item * item) {
  this->items.push_back(item);
}

/**
 * Add actor to chunk
 * \param actor Actor to add
 */
void Chunk::AddActor(Actor * actor) {
  this->actors.push_back(actor);
}

/**
 * Add physical object to chunk
 * \param object Object to add
 */
void Chunk::AddObject(PhysicalObj * object) {
  this->objects.push_back(object);
}

/**
 * Get item from chunk by index
 * \param index Index of item to get
 * \return Pointer to item on this position
 */
Item * Chunk::GetItem(int index) {
  if (index < 0 || index >= this->GetItemsCount())
    return nullptr;
  return this->items[index];
}

/**
 * Get actor from chunk by index
 * \param index Index of actor to get
 * \return Pointer to actor on this position
 */
Actor * Chunk::GetActor(int index) {
  if (index < 0 || index >= this->GetActorsCount())
    return nullptr;
  return this->actors[index];
}

/**
 * Get object from chunk by index
 * \param index Index of object to get
 * \return Pointer to object on this position
 */
PhysicalObj * Chunk::GetObject(int index) {
  if (index < 0 || index >= this->GetObjectsCount())
    return nullptr;
  return this->objects[index];
}

/**
 * Delete item from chunk by index
 * \param index Index of object to delete
 */
void Chunk::DeleteItem(int index) {
  if (index < 0 || index >= this->GetItemsCount())
    return;
  this->items.erase(this->items.begin() + index);
}

/**
 * Delete actor from chunk by index
 * \param index Index of object to delete
 */
void Chunk::DeleteActor(int index) {
  if (index < 0 || index >= this->GetActorsCount())
    return;
  this->actors.erase(this->actors.begin() + index);
}

/**
 * Delete object from chunk by index
 * \param index Index of object to delete
 */
void Chunk::DeleteObject(int index) {
  if (index < 0 || index >= this->GetObjectsCount())
    return;
  this->objects.erase(this->objects.begin() + index);
}

/**
 * Update physics of all objects in this chunk
 * \warning Player is not updated!
 * \param dt Time passed since last update
 */
void Chunk::Update(float dt) {
  for(int actor_i = 0; actor_i < this->GetActorsCount(); actor_i++) {
    this->actors[actor_i]->
      GetPhysicalObj()->
      collideTerrain(this->terrain, glm::vec2(0.0f, 0.0f), VCAP);
  }

  for(int object_i = 0; object_i < this->GetObjectsCount(); object_i++) {
    this->objects[object_i]->
      collideTerrain(this->terrain, glm::vec2(0.0f, 0.0f), VCAP);
  }
  
  for(int item_i = 0; item_i < this->GetItemsCount(); item_i++) {
    this->items[item_i]->
      GetPhysicalObj()->
      collideTerrain(this->terrain, glm::vec2(0.0f, 0.0f), VCAP);
  }

  for(int actor_i = 0; actor_i < this->GetActorsCount(); actor_i++)
    this->actors[actor_i]->GetPhysicalObj()->update(dt);

  for(int object_i = 0; object_i < this->GetObjectsCount(); object_i++)
    this->objects[object_i]->update(dt);
  
  for(int item_i = 0; item_i < this->GetItemsCount(); item_i++)
    this->items[item_i]->GetPhysicalObj()->update(dt);
}
