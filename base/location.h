/**
 * \file
 * \brief This file contains declaraion of Location and its helper functions
 */

/**
 * \brief Location is a place that consists of pieces (Chunk)
 */
#ifndef LOCATION_H
#define LOCATION_H

#include "chunk.h"

class Location {
 private:
  int chunk_width, chunk_height;
  int width, height;
  vector<vector<Chunk *>> chunks;
 public:
  Location(int, int, int, int);
  void FillEmptyChunks();
  void SetChunk(int, int, Chunk *);
  Chunk * GetChunk(int, int);
  Chunk * GetCurrentChunk(float, float);

  void Draw(ShaderHolder *, Camera *, int, int, float, float);
};

#endif
