/**
 * \file
 * \brief This file contains implementation of Location and its helper functions
 */
#include "location.hpp"

/**
 * Default constructor
 * \param width Width of this location (in chunks)
 * \param height Height of this location (in chunks)
 * \param chunk_width Width of chunk (in meters)
 * \param chunk_height Height of chunk (in meters)
 */
Location::Location(int width, int height, int chunk_width, int chunk_height) {
  this->width = width;
  this->height = height;
  this->chunk_width = chunk_width;
  this->chunk_height = chunk_height;

  for(int i = 0; i < height; i++) {
    vector<Chunk *> row;
    for(int j = 0; j < width; j++) {
      row.push_back(nullptr);
    }
    this->chunks.push_back(row);
  }

  this->current_x = 0;
  this->current_y = 0;
}

/**
 * Fill empty chunks with plain terrain
 */
void Location::FillEmptyChunks() {
  for(int i = 0; i < this->height; i++) {
    for(int j = 0; j < this->width; j++) {
      if(this->chunks[i][j] == nullptr) {
	this->chunks[i][j] = new Chunk(new Terrain(this->chunk_width, 40, glm::vec3(this->chunk_width * i,
										    -1.0f,
										    this->chunk_height * j)),
                        4.0f);
      }
    }
  }
}

/**
 * Set chunk at position
 * \param x Row
 * \param y Column
 * \param chunk New chunk
 */
void Location::SetChunk(int x, int y, Chunk * chunk) {
  this->chunks[x][y] = chunk;
}

/**
 * Get chunk at indexes
 * \param x Row
 * \param y Column
 * \return Pointer to chunk at this position
 */
Chunk * Location::GetChunk(int x, int y) {
  if(x < 0 || y < 0 || x >= height || y >= width) return nullptr;
  return this->chunks[x][y];
}

/**
 * Get current chunk (Position of current chunk is taken from Location::UpdatePosition())
 * \return Pointer to chunk
 */
Chunk * Location::GetCurrentChunk() {
  if(this->current_x < 0 || this->current_y < 0 || this->current_x >= height || this->current_y >= width) return nullptr;
  return this->chunks[this->current_x][this->current_y];
}

/**
 * Get chunk by position
 * \param x X coord
 * \param y Y coord
 * \return Pointer to chunk at position
 */
Chunk * Location::GetChunkByPosition(float x, float y) {
  int px = x / this->chunk_width;
  int py = y / this->chunk_height;

   if(px < 0 || py < 0 || px >= height || py >= width) return nullptr;
  
  return this->chunks[px][py];
}

void Location::UpdatePosition(glm::vec3 pos) {
  this->current_x = pos.x / this->chunk_width;
  this->current_y = pos.z / this->chunk_height;
}

/**
 * Draw all chunks around current chunk (Position of current chunk
 * is taken from Location::UpdatePosition())
 * \param shaderHolder Pointer to all shaders
 * \param camera Pointer to camer
 * \param screen_width Width of screen
 * \param screen_height Height of screen
 */
void Location::Draw(ShaderHolder * shaderHolder, Camera * camera, int screen_width, int screen_height) {
  int lx = max(this->current_x - 3, 0); // Most left row
  int uy = max(this->current_y - 3, 0); // Most up column
  int rx = min(this->current_x + 3, this->width - 1); // Most right row
  int dy = min(this->current_y + 3, this->height - 1); // Most down column

  
  for(int ix = lx; ix <= rx; ix++) {
    for(int iy = uy; iy <= dy; iy++) {
      if(this->chunks[ix][iy] != nullptr) {
        this->chunks[ix][iy]->Draw(shaderHolder, camera, screen_width, screen_height);
      }
    }
  }

  for(int ix = lx; ix <= rx; ix++) {
    for(int iy = uy; iy <= dy; iy++) {
      if(this->chunks[ix][iy] != nullptr) {
        this->chunks[ix][iy]->DrawWater(shaderHolder, camera, screen_width, screen_height);
      }
    }
  }
}

// Global functions and objects

Location * current_location;

Location * GetCurrentLocation() {
  return current_location;
}

void SetCurrentLocation(Location *loc) {
  current_location = loc;
}
