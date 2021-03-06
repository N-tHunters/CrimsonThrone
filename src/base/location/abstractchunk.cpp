#include "abstractchunk.hpp"
#include "chunkloader.hpp"

/**
 * Basic constructor
 */
AbstractChunk::AbstractChunk(Location * location, unsigned short x, unsigned short y, ChunkLoader * chunk_loader) {
  this->water_obj = nullptr;
  this->location = location;
  this->x = x;
  this->y = y;
  this->chunk_loader = chunk_loader;
  this->is_loaded = false;
}

void AbstractChunk::LoadTerrain(Terrain * terrain) {
  this->terrain = terrain;
}

void AbstractChunk::LoadABS() {
  if(is_loaded) return;
  
  chunk_loader->Load(this);
  delete chunk_loader;
  
  is_loaded = true;
}
