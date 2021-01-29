/**
 * \file
 * \brief This file contains implementation of Chunk
 */
#include "chunk.hpp"
#include "location.hpp"

/// Maximum velocity
#define VCAP 0.1f

/***
 * Empty constructor
 * \warning Should not use
 */
Chunk::Chunk() {
  this->is_water_present = false;
  this->water_obj = nullptr;
  this->location = nullptr;
}

/**
 * Basic constructor
 * \param terrain Landscape of this chunk
 */
Chunk::Chunk(Location * location, unsigned short x, unsigned short y, Terrain * terrain) : Chunk() {
  this->terrain = terrain;
  this->water_obj = nullptr;
  this->location = location;
  this->x = x;
  this->y = y;
}

/**
 * Constructor with water
 * \param terrain Landscape of this chunk
 * \param water_height Water level
 */
Chunk::Chunk(Location * location, unsigned short x, unsigned short y, Terrain * terrain, float water_height) : Chunk(location, x, y, terrain) {
  this->is_water_present = true;
  this->water_height = water_height;
  
  std::vector<float> *vertices = new std::vector<float>;
  std::vector<unsigned int> *indices = new std::vector<unsigned int>;

  vertices->clear();
  indices->clear();

  int vertices_number = 40;

  float tile_width = terrain->getSize() / (vertices_number - 1);

  for(int i = 0; i < vertices_number - 1; i ++) {
    for(int j = 0; j < vertices_number - 1; j ++) {
      vertices->push_back(i * tile_width);
      vertices->push_back(water_height);
      vertices->push_back(j * tile_width);

      vertices->push_back(0.0f);
      vertices->push_back(1.0f);
      vertices->push_back(0.0f);

      vertices->push_back(0.0f);
      vertices->push_back(0.0f);

      vertices->push_back((i + 1) * tile_width);
      vertices->push_back(water_height);
      vertices->push_back(j * tile_width);

      vertices->push_back(0.0f);
      vertices->push_back(1.0f);
      vertices->push_back(0.0f);

      vertices->push_back(1.0f);
      vertices->push_back(0.0f);

      vertices->push_back(i * tile_width);
      vertices->push_back(water_height);
      vertices->push_back((j + 1) * tile_width);

      vertices->push_back(0.0f);
      vertices->push_back(1.0f);
      vertices->push_back(0.0f);

      vertices->push_back(0.0f);
      vertices->push_back(1.0f);

      indices->push_back(i * (vertices_number - 1) * 6 + j * 6);
      indices->push_back(i * (vertices_number - 1) * 6  + j * 6 + 1);
      indices->push_back(i * (vertices_number - 1) * 6  + j * 6 + 2);

      vertices->push_back((i + 1) * tile_width);
      vertices->push_back(water_height);
      vertices->push_back(j * tile_width);

      vertices->push_back(0.0f);
      vertices->push_back(1.0f);
      vertices->push_back(0.0f);

      vertices->push_back(1.0f);
      vertices->push_back(0.0f);

      vertices->push_back((i + 1) * tile_width);
      vertices->push_back(water_height);
      vertices->push_back((j + 1) * tile_width);

      vertices->push_back(0.0f);
      vertices->push_back(1.0f);
      vertices->push_back(0.0f);

      vertices->push_back(1.0f);
      vertices->push_back(1.0f);

      vertices->push_back(i * tile_width);
      vertices->push_back(water_height);
      vertices->push_back((j + 1) * tile_width);

      vertices->push_back(0.0f);
      vertices->push_back(1.0f);
      vertices->push_back(0.0f);

      vertices->push_back(0.0f);
      vertices->push_back(1.0f);

      indices->push_back(i * (vertices_number - 1) * 6 + j * 6 + 3);
      indices->push_back(i * (vertices_number - 1) * 6  + j * 6 + 4);
      indices->push_back(i * (vertices_number - 1) * 6  + j * 6 + 5);
    }
  }

  this->water_obj = new PhysicalObj(new Mesh("resources/textures/water.jpeg", vertices, indices, 2),
                                    false,
                                    true,
                                    false,
                                    false,
                                    terrain->getPosition(),
                                    glm::vec3(0.0f, 0.0f, 0.0f),
                                    "water");
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
  for(size_t i = 0; i <  this->GetObjsCount(); i ++) {
    this->objects[i]->draw(shaderHolder, camera, width, height);
  }
  for(size_t i = 0; i <  this->GetActorsCount(); i ++) {
    this->actors[i]->GetPhysicalObj()->draw(shaderHolder, camera, width, height);
  }
  for(size_t i = 0; i <  this->GetItemsCount(); i ++) {
    this->items[i]->GetPhysicalObj()->draw(shaderHolder, camera, width, height);
  }
}

void Chunk::DrawWater(ShaderHolder * shaderHolder, Camera * camera, int width, int height) {
  if(this->water_obj != nullptr) {
    this->water_obj->draw(shaderHolder, camera, width, height);
  }
}

/**
 * Get number of items in this chunk
 * \return Number of items
 */
size_t Chunk::GetItemsCount() {
  return this->items.size();
}

/**
 * Get number of actors in this chunk
 * \return Number of actors
 */
size_t Chunk::GetActorsCount() {
  return this->actors.size();
}

/**
 * Get number of objects in this chunk
 * \return Number of objects
 */
size_t Chunk::GetObjsCount() {
  return this->objects.size();
}

/**
 * Get number of triggers
 * \return Number of triggers
 */
size_t Chunk::GetTriggersCount() {
  return this->triggers.size();
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
 * \param object Obj to add
 */
void Chunk::AddObj(PhysicalObj * object) {
  this->objects.push_back(object);
}

/**
 * Add trigger to chunk
 * \param trigger BoundaryTrigger to add 
 */
void Chunk::AddTrigger(BoundaryTrigger * trigger) {
  this->triggers.push_back(trigger);
}

/**
 * Get item from chunk by index
 * \param index Index of item to get
 * \return Pointer to item on this position
 */
Item * Chunk::GetItem(size_t index) {
  if (index < 0 || index >= this->GetItemsCount())
    return nullptr;
  return this->items[index];
}

/**
 * Get actor from chunk by index
 * \param index Index of actor to get
 * \return Pointer to actor on this position
 */
Actor * Chunk::GetActor(size_t index) {
  if (index < 0 || index >= this->GetActorsCount())
    return nullptr;
  return this->actors[index];
}

/**
 * Get object from chunk by index
 * \param index Index of object to get
 * \return Pointer to object on this position
 */
PhysicalObj * Chunk::GetObj(size_t index) {
  if (index < 0 || index >= this->GetObjsCount())
    return nullptr;
  return this->objects[index];
}

/**
 * Get trigger from chunk by index
 * \param index Index of trigger to get
 * \return Pointer to trigger
 */
BoundaryTrigger * Chunk::GetTrigger(size_t index) {
  if (index < 0 || index >= this->GetTriggersCount())
    return nullptr;
  return this->triggers[index];
}

/**
 * Delete item from chunk by index
 * \param index Index of object to delete
 */
void Chunk::DeleteItemByIndex(size_t index) {
  if (index < 0 || index >= this->GetItemsCount())
    return;
  this->items.erase(this->items.begin() + index);
}

/**
 * Delete actor from chunk by index
 * \param index Index of object to delete
 */
void Chunk::DeleteActorByIndex(size_t index) {
  if (index < 0 || index >= this->GetActorsCount())
    return;
  this->actors.erase(this->actors.begin() + index);
}

/**
 * Delete object from chunk by index
 * \param index Index of object to delete
 */
void Chunk::DeleteObjByIndex(size_t index) {
  if (index < 0 || index >= this->GetObjsCount())
    return;
  this->objects.erase(this->objects.begin() + index);
}

/**
 * Delete triggers from chunk by index
 * \param index Index of trigger to delete
 */
void Chunk::DeleteTriggerByIndex(size_t index) {
  if (index < 0 || index >= this->GetObjsCount())
    return;
  this->triggers.erase(this->triggers.begin() + index);
}

/**
 * Delete object from chunk by pointer
 * \param object Pointer to object
 */
void Chunk::DeleteObj(PhysicalObj * object) {
  for(size_t i = 0; i < objects.size(); i++)
    if(objects[i] == object) {
      objects.erase(objects.begin() + i);
      return;
    }
}

/**
 * Delete actor from chunk by pointer
 * \param actor Pointer to actor
 */
void Chunk::DeleteActor(Actor * actor) {
  for(size_t i = 0; i < actors.size(); i++)
    if(actors[i] == actor) {
      actors.erase(actors.begin() + i);
      return;
    }
}

/**
 * Collide given PhysicalObj with all objects in chunk (except items)
 * \param obj Object to collide
 * \param dt Time passed since last call
 */
void Chunk::CollideWithAll(PhysicalObj * obj, float dt, bool isPlayer) {
  // glm::vec3 result(1.0f, 1.0f, 1.0f);

  for(size_t object_i = 0; object_i < this->GetObjsCount(); object_i++) {
    if(this->GetObj(object_i) != obj)
      obj->collide(this->GetObj(object_i), dt, obj->velocity, isPlayer);
  }
		
  for(size_t actor_i = 0; actor_i < this->GetActorsCount(); actor_i++) {
    if(this->GetActor(actor_i)->GetPhysicalObj() != obj)
      obj->collide(this->GetActor(actor_i)->GetPhysicalObj(), dt, obj->velocity, isPlayer);
  }
  // obj->velocity *= result;
}

/**
 * Collides object with all other objects in chunk (except items)
 * \param dt Time passed since last call
 */
void Chunk::CollideAll(float dt) {
  for(size_t actor_i = 0; actor_i < this->GetActorsCount(); actor_i++) {
    this->CollideWithAll(this->GetActor(actor_i)->GetPhysicalObj(), dt, false);
  }

  for(size_t object_i = 0; object_i < this->GetObjsCount(); object_i++) {
    this->CollideWithAll(this->GetObj(object_i), dt, false);
  }
  
  for(size_t item_i = 0; item_i < this->GetItemsCount(); item_i++) {
    this->CollideWithAll(this->GetItem(item_i)->GetPhysicalObj(), dt, false);
  }
}


void Chunk::CheckAllTriggers(PhysicalObj * obj) {
  for(BoundaryTrigger * trigger : triggers) {
    if(obj->boundary->Collide(trigger->GetBoundary(), obj->getPosition(), obj->getRotation(), trigger->GetPosition(), glm::vec3(0.f, 0.f, 0.f)))
      trigger->Trig(this, obj);
  }
}

void Chunk::TriggerAll() {
  for(size_t actor_i = 0; actor_i < this->GetActorsCount(); actor_i++) {
    this->CheckAllTriggers(this->GetActor(actor_i)->GetPhysicalObj());
  }

  for(size_t object_i = 0; object_i < this->GetObjsCount(); object_i++) {
    this->CheckAllTriggers(this->GetObj(object_i));
  }
  
  for(size_t item_i = 0; item_i < this->GetItemsCount(); item_i++) {
    this->CheckAllTriggers(this->GetItem(item_i)->GetPhysicalObj());
  }
}

/**
 * Update physics of all objects in this chunk
 * \warning Player is not updated!
 * \param dt Time passed since last update
 */
void Chunk::Update(float dt) {
  CollideAll(dt);
  TriggerAll();
  
  for(Actor * actor : actors)
    actor->GetPhysicalObj()->update(dt);

  for(PhysicalObj * object : objects)
    object->update(dt);
  
  for(Item * item : items)
    item->GetPhysicalObj()->update(dt);

  for(Actor * actor : actors)
    actor->GetPhysicalObj()->collideTerrain(terrain, dt, this);

  for(PhysicalObj * object : objects)
    object->collideTerrain(terrain, dt, this);
  
  for(Item * item : items)
    item->GetPhysicalObj()->collideTerrain(terrain, dt, this);


  // Check if any object went into another chunk
  
  for(Actor * actor: actors) {
    glm::vec3 position = actor->GetPhysicalObj()->getPosition();
    Chunk * chunk_ptr = this->location->GetChunkByPosition(position.x, position.y);
    if(chunk_ptr != this) {
      this->DeleteActor(actor);
      if(chunk_ptr != nullptr)
	chunk_ptr->AddActor(actor);
    }
  }
  
  for(PhysicalObj * object: objects) {
    glm::vec3 position = object->getPosition();
    Chunk * chunk_ptr = this->location->GetChunkByPosition(position.x, position.y);
    if(chunk_ptr != this) {
      this->DeleteObj(object);
      if(chunk_ptr != nullptr)
	chunk_ptr->AddObj(object);
    }
  }
  
}



bool Chunk::IsWaterPresent() { return this->is_water_present; }
void Chunk::SetWaterHeight(float water_height) { this->water_height = water_height; }
float Chunk::GetWaterHeight() { return this->water_height; }

Location * Chunk::GetLocation() { return location; }
void Chunk::SetLocation(Location * location) { this->location = location; }
