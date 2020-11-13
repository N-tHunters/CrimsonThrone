#include "chunk.h"

#define VCAP 0.1f;

Chunk::Chunk() {}

Chunk::Chunk(Terrain * terrain) {
  this->terrain = terrain;
  printf("Chunk was created\n");
}

Terrain * Chunk::GetTerrain() {
  return this->terrain;
}

void Chunk::Draw(Shader * shader, Camera * camera, int width, int height) {
  this->terrain->draw(shader, camera, width, height);
  for(int i = 0; i <  this->GetObjectsCount(); i ++) {
    this->objects[i]->draw(shader, camera, width, height);
  }
  for(int i = 0; i <  this->GetActorsCount(); i ++) {
    this->actors[i]->GetPhysicalObj()->draw(shader, camera, width, height);
  }
  for(int i = 0; i <  this->GetItemsCount(); i ++) {
    this->items[i]->GetPhysicalObj()->draw(shader, camera, width, height);
  }
}

int Chunk::GetItemsCount() {
  return this->items.size();
}

int Chunk::GetActorsCount() {
  return this->actors.size();
}

int Chunk::GetObjectsCount() {
  return this->objects.size();
}

void Chunk::AddItem(Item * item) {
  this->items.push_back(item);
}

void Chunk::AddActor(Actor * actor) {
  this->actors.push_back(actor);
}

void Chunk::AddObject(PhysicalObj * object) {
  this->objects.push_back(object);
}

Item * Chunk::GetItem(int index) {
  if (index < 0 || index >= this->GetItemsCount())
    return nullptr;
  return this->items[index];
}

Actor * Chunk::GetActor(int index) {
  if (index < 0 || index >= this->GetActorsCount())
    return nullptr;
  return this->actors[index];
}

PhysicalObj * Chunk::GetObject(int index) {
  if (index < 0 || index >= this->GetObjectsCount())
    return nullptr;
  return this->objects[index];
}

void Chunk::DeleteItem(int index) {
  if (index < 0 || index >= this->GetItemsCount())
    return;
  this->items.erase(this->items.begin() + index);
}

void Chunk::DeleteActor(int index) {
  if (index < 0 || index >= this->GetActorsCount())
    return;
  this->actors.erase(this->actors.begin() + index);
}

void Chunk::DeleteObject(int index) {
  if (index < 0 || index >= this->GetObjectsCount())
    return;
  this->objects.erase(this->objects.begin() + index);
}

void Chunk::Update(float dt) {
  for(int actor_i = 0; actor_i < this->GetActorsCount(); actor_i++) {
    this->actors[actor_i]->
      GetPhysicalObj()->
      collideTerrain(this->terrain, glm::vec2(0.0f, 0.0f), 0.1);
  }

  for(int actor_i = 0; actor_i < this->GetActorsCount(); actor_i++)
    this->actors[actor_i]->GetPhysicalObj()->update(dt);
}
