/**
 * \file
 * \brief This file contains implementation of Location and its helper functions
 */
#include "location.hpp"

const int PROCESS_RADIUS = 3;
const int RENDER_RADIUS = 5;

/**
 * Default constructor
 * \param width Width of this location (in chunks)
 * \param height Height of this location (in chunks)
 * \param chunk_width Width of chunk (in meters)
 * \param chunk_height Height of chunk (in meters)
 */
Location::Location(size_t width, size_t height, int chunk_width, int chunk_height) {
  this->width = width;
  this->height = height;
  this->chunk_width = chunk_width;
  this->chunk_height = chunk_height;

  for(size_t i = 0; i < height; i++) {
    vector<Chunk *> row;
    for(size_t j = 0; j < width; j++) {
      row.push_back(nullptr);
    }
    this->chunks.push_back(row);
  }

  this->current_x = 0;
  this->current_y = 0;
}

/**
 * Construct location from landscape generator
 * \param width Width of this location (in chunks)
 * \param height Height of this location (in chunks)
 * \param chunk_width Width of chunk (in meters)
 * \param chunk_height Height of chunk (in meters)
 */
Location::Location(size_t width, size_t height, int chunk_width, int chunk_height, LandscapeGenerator * generator) {
  this->width = width;
  this->height = height;
  this->chunk_width = chunk_width;
  this->chunk_height = chunk_height;

  for(size_t i = 0; i < height; i++) {
    vector<Chunk *> row;
    for(size_t j = 0; j < width; j++) {
      row.push_back(nullptr);
    }
    this->chunks.push_back(row);
  }

  generator->Generate(this, width, height, chunk_width, chunk_height, 10);

  this->current_x = 0;
  this->current_y = 0;
}


/**
 * Fill empty chunks with plain terrain
 */
void Location::FillEmptyChunks() {
  for(size_t i = 0; i < height; i++)
    for(size_t j = 0; j < width; j++)
      if(chunks[i][j] == nullptr)
	chunks[i][j] = new Chunk(this, i, j, new Terrain(chunk_width, 11, glm::vec3(chunk_width * i, -1.0f, chunk_height * j)), 1.0f);
}

/**
 * Set chunk at position
 * \param x Row
 * \param y Column
 * \param chunk New chunk
 */
void Location::SetChunk(size_t x, size_t y, Chunk * chunk) {
  chunks[x][y] = chunk;
}

/**
 * Get chunk at indexes
 * \param x Row
 * \param y Column
 * \return Pointer to chunk at this position
 */
Chunk * Location::GetChunk(size_t x, size_t y) {
  if(x >= height || y >= width) return nullptr;
  return chunks[x][y];
}

/**
 * Get current chunk (Position of current chunk is taken from Location::UpdatePosition())
 * \return Pointer to chunk
 */
Chunk * Location::GetCurrentChunk() {
  if(current_x >= height || current_y >= width) return nullptr;
  return chunks[current_x][current_y];
}

/**
 * Get chunk by position
 * \param x X coord
 * \param y Y coord
 * \return Pointer to chunk at position
 */
Chunk * Location::GetChunkByPosition(float x, float y) {
  int px = x / chunk_width;
  int py = y / chunk_height;

  if(px < 0 || py < 0 || px >= (int)height || py >= (int)width) return nullptr;
  
  return chunks[px][py];
}

void Location::UpdatePosition(glm::vec3 pos) {
  current_x = pos.x / chunk_width;
  current_y = pos.z / chunk_height;
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
  int lx = max((int)current_x - RENDER_RADIUS, 0); // Most left row
  int uy = max((int)current_y - RENDER_RADIUS, 0); // Most up column
  int rx = min((int)current_x + RENDER_RADIUS, (int)width - 1); // Most right row
  int dy = min((int)current_y + RENDER_RADIUS, (int)height - 1); // Most down column

  
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

void Location::Update(float dt) {
  int lx = max((int)current_x - PROCESS_RADIUS, 0); // Most left row
  int uy = max((int)current_y - PROCESS_RADIUS, 0); // Most up column
  int rx = min((int)current_x + PROCESS_RADIUS, (int)width - 1); // Most right row
  int dy = min((int)current_y + PROCESS_RADIUS, (int)height - 1); // Most down column

  
  for(int ix = lx; ix <= rx; ix++) {
    for(int iy = uy; iy <= dy; iy++) {
      if(this->chunks[ix][iy] != nullptr) {
        this->chunks[ix][iy]->Update(dt);
      }
    }
  }

}
