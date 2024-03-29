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
#include <base/actors/player.hpp>

class Location {
 private:
  int chunk_width, chunk_height;
  size_t width, height;
  std::vector<std::vector<Chunk *>> chunks;
  size_t current_x, current_y;
  
 public:
  Location(size_t, size_t, int, int);
  Location(size_t, size_t, int, int, LandscapeGenerator *);
  Location(size_t, size_t, int, int, int, LandscapeGenerator *);
  
  void FillEmptyChunks();
  void SetChunk(size_t, size_t, Chunk *);
  Chunk * GetChunk(size_t, size_t);
  Chunk * GetChunkByPosition(float, float);
  Chunk * GetCurrentChunk();
  void UpdatePosition(glm::vec3);

  void Draw(Camera *, Player *);
  void Update(float);
  void LoadABS();
  std::pair<Actor *, float> CollideActorsWithRay(glm::vec3, glm::vec3);
  std::pair<Item *, float> CollideItemsWithRay(glm::vec3, glm::vec3);
};

Location * GetCurrentLocation();
void SetCurrentLocation(Location *);

#endif
