#include "abstractchunk.hpp"
#include "chunkloader.hpp"
#include <future>

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
  this->load_state = 0;
  this->height_map = nullptr;
}

void AbstractChunk::LoadTerrain(Terrain * terrain) {
  this->terrain = terrain;
}

void AbstractChunk::LoadABS() {
  if(is_loaded) return;

  if(load_state == 0) {
    loading_thread = new std::thread(&ChunkLoader::Load, chunk_loader, this);
    load_state = 1;
  } else if(load_state == 1) {
    if (height_map != nullptr) {
      assert(blend_pixels.size() != 0);
      LoadTerrain(new Terrain(size, vertices_number, position, height_map, texture1, texture2, 1.0f, blend_pixels));
      load_state = 2;
    }
  } else {
    if(chunk_loader->AreObjectsLoaded())
      this->SetLoaded();
    else
      chunk_loader->LoadObjects(this);
  }
}

void AbstractChunk::SetLoaded() {
  this->is_loaded = true;
}

bool AbstractChunk::IsLoaded() {
  return this->is_loaded;
}

void AbstractChunk::SetHeightMap(std::vector<std::vector<float>> * height_map,
                                 float size,
                                 int vertices_number,
                                 glm::vec3 position,
                                 GLuint texture1,
                                 GLuint texture2,
                                 std::vector<unsigned char> blend_pixels) {
  this->size = size;
  this->vertices_number = vertices_number;
  this->position = position;
  this->texture1 = texture1;
  this->texture2 = texture2;
  this->blend_pixels = blend_pixels;
  this->height_map = height_map;
}