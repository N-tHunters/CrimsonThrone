/**
 * \file
 * \brief This file contains implementation of Location and its helper functions
 */
#include "location.h"

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
}

/**
 * Fill empty chunks with plain terrain
 */
void Location::FillEmptyChunks() {
  for(int i = 0; i < this->height; i++) {
    for(int j = 0; j < this->width; j++) {
      if(this->chunks[i][j] == nullptr) {
	this->chunks[i][j] = new Chunk(new Terrain(chunk_width, 0.1f));
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
 * Get chunk at position
 * \param x Row
 * \param y Column
 * \return Pointer to chunk at this position
 */
Chunk * Location::GetChunk(int x, int y) {
  return this->chunks[x][y];
}

/**
 * Draw all chunks around current chunk
 * \param shaderHolder Pointer to all shaders
 * \param camera Pointer to camer
 * \param screen_width Width of screen
 * \param screen_height Height of screen
 * \param xp X coordinate of current position
 * \param yp Y coordinate of current position
 */
void Location::Draw(ShaderHolder * shaderHolder, Camera * camera, int screen_width, int screen_height, int xp, int yp) {
  int x = xp / this->chunk_width;
  int y = yp / this->chunk_height;

  int lx = max(x - 1, 0); // Most left row
  int uy = max(y - 1, 0); // Most up column
  int rx = min(x + 1, this->width - 1); // Most right row
  int dy = min(y + 1, this->height - 1); // Most down column
  
  for(int ix = lx; ix <= rx; ix++) {
    for(int iy = uy; iy <= dy; uy++) {
      if(this->chunks[ix][iy] != nullptr)
	this->chunks[ix][iy]->Draw(shaderHolder, camera, screen_width, screen_height);
    }
  }
}
