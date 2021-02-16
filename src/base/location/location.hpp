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
#include <landscape/landscapegenerator.hpp>

class Location {
 private:
  int chunk_width, chunk_height;
  size_t width, height;
  std::vector<std::vector<Chunk *>> chunks;
  size_t current_x, current_y;
  
 public:
  Location(size_t, size_t, int, int);
  Location(size_t, size_t, int, int, LandscapeGenerator *);
  void FillEmptyChunks();
  void SetChunk(size_t, size_t, Chunk *);
  Chunk * GetChunk(size_t, size_t);
  Chunk * GetChunkByPosition(float, float);
  Chunk * GetCurrentChunk();
  void UpdatePosition(glm::vec3);

  void Draw(ShaderHolder *, Camera *, int, int);
  void Update(float);
};


void init_demo_locations();
Location * GetCurrentLocation();
void SetCurrentLocation(Location *);

#endif
