/**
 * \file
 * \brief This file contains declaraion of Location and its helper functions
 */

/**
 * \brief Location is a place that consists of pieces (Chunk)
 */
#ifndef LOCATION_H
#define LOCATION_H

#include "chunk.hpp"

class Location {
 private:
  int chunk_width, chunk_height;
  int width, height;
  vector<vector<Chunk *>> chunks;
  int current_x, current_y;
  
 public:
  Location(int, int, int, int);
  void FillEmptyChunks();
  void SetChunk(int, int, Chunk *);
  Chunk * GetChunk(int, int);
  Chunk * GetChunkByPosition(float, float);
  Chunk * GetCurrentChunk();
  void UpdatePosition(glm::vec3);

  void Draw(ShaderHolder *, Camera *, int, int);
};


Location * GetCurrentLocation();
void SetCurrentLocation(Location *);

#endif
