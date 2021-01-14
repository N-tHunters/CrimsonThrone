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
Chunk::Chunk() {
  this->is_water_present = false;
  this->water_obj = nullptr;
}

/**
 * Basic constructor
 * \param terrain Landscape of this chunk
 */
Chunk::Chunk(Terrain * terrain) : Chunk() {
  this->terrain = terrain;
  this->water_obj = nullptr;
}

/**
 * Constructor with water
 * \param terrain Landscape of this chunk
 * \param water_height Water level
 */
Chunk::Chunk(Terrain * terrain, float water_height) : Chunk(terrain) {
  this->is_water_present = true;
  this->water_height = water_height;
  std::vector<float> *vertices = new std::vector<float> {
    -1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f,  1.0f, 0.0f, 1.0f,
     1.0f, 0.0f,  1.0f, 1.0f, 1.0f,
     1.0f, 0.0f, -1.0f, 1.0f, 0.0f
  };
  std::vector<unsigned int> *indices = new std::vector<unsigned int> {
    0, 1, 2,
    0, 2, 3
  };
  this->water_obj = new PhysicalObj(new Mesh("resources/textures/water.png", vertices, indices),
                                    false,
                                    true,
                                    false,
                                    false,
                                    terrain->getPosition() + glm::vec3(0.0f, water_height, 0.0f),
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
  for(int i = 0; i <  this->GetObjsCount(); i ++) {
    this->objects[i]->draw(shaderHolder, camera, width, height);
  }
  for(int i = 0; i <  this->GetActorsCount(); i ++) {
    this->actors[i]->GetPhysicalObj()->draw(shaderHolder, camera, width, height);
  }
  for(int i = 0; i <  this->GetItemsCount(); i ++) {
    this->items[i]->GetPhysicalObj()->draw(shaderHolder, camera, width, height);
  }
  if(this->water_obj != nullptr) {
    this->water_obj->draw(shaderHolder, camera, width, height);
  } else {
    printf("%s\n", "NULLPTR");
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
int Chunk::GetObjsCount() {
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
 * \param object Obj to add
 */
void Chunk::AddObj(PhysicalObj * object) {
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
PhysicalObj * Chunk::GetObj(int index) {
  if (index < 0 || index >= this->GetObjsCount())
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
void Chunk::DeleteObj(int index) {
  if (index < 0 || index >= this->GetObjsCount())
    return;
  this->objects.erase(this->objects.begin() + index);
}

/**
 * Collide given PhysicalObj with all objects in chunk (except items)
 * \param obj Object to collide
 * \param dt Time passed since last call
 */
void Chunk::CollideWithAll(PhysicalObj * obj, float dt) {
  glm::vec3 result(1.0f, 1.0f, 1.0f);

  for(int object_i = 0; object_i < this->GetObjsCount(); object_i++) {
    if(this->GetObj(object_i) != obj)
      result *= obj->collide(this->GetObj(object_i), dt, obj->velocity);
  }
		
  for(int actor_i = 0; actor_i < this->GetActorsCount(); actor_i++) {
    if(this->GetActor(actor_i)->GetPhysicalObj() != obj)
      result *= obj->collide(this->GetActor(actor_i)->GetPhysicalObj(), dt, obj->velocity);
  }
  obj->velocity *= result;
}

/**
 * Collides object with all other objects in chunk (except items)
 * \param dt Time passed since last call
 */
void Chunk::CollideAll(float dt) {
  for(int actor_i = 0; actor_i < this->GetActorsCount(); actor_i++) {
    this->CollideWithAll(this->GetActor(actor_i)->GetPhysicalObj(), dt);
  }

  for(int object_i = 0; object_i < this->GetObjsCount(); object_i++) {
    this->CollideWithAll(this->GetObj(object_i), dt);
  }
  
  for(int item_i = 0; item_i < this->GetItemsCount(); item_i++) {
    this->CollideWithAll(this->GetItem(item_i)->GetPhysicalObj(), dt);
  }
}

/**
 * Update physics of all objects in this chunk
 * \warning Player is not updated!
 * \param dt Time passed since last update
 */
void Chunk::Update(float dt) {
  this->CollideAll(dt);
  
  for(int actor_i = 0; actor_i < this->GetActorsCount(); actor_i++)
    this->actors[actor_i]->GetPhysicalObj()->update(dt);

  for(int object_i = 0; object_i < this->GetObjsCount(); object_i++)
    this->objects[object_i]->update(dt);
  
  for(int item_i = 0; item_i < this->GetItemsCount(); item_i++)
    this->items[item_i]->GetPhysicalObj()->update(dt);

  for(int actor_i = 0; actor_i < this->GetActorsCount(); actor_i++) {
    this->actors[actor_i]->
      GetPhysicalObj()->
      collideTerrain(this->terrain, dt);
  }

  for(int object_i = 0; object_i < this->GetObjsCount(); object_i++) {
    this->objects[object_i]->
      collideTerrain(this->terrain, dt);
  }
  
  for(int item_i = 0; item_i < this->GetItemsCount(); item_i++) {
    this->items[item_i]->
      GetPhysicalObj()->
      collideTerrain(this->terrain, dt);
  }
}


bool Chunk::IsWaterPresent() { return this->is_water_present; }
void Chunk::SetWaterHeight(float water_height) { this->water_height = water_height; }
float Chunk::GetWaterHeight() { return this->water_height; }
