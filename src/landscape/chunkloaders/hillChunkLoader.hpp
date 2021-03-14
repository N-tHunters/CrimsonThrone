#pragma once

#include <base/location/chunkloader.hpp>
#include <noise/noise.h>

class HillChunkLoader : public ChunkLoader {
  float size;
  int vertices_number;
  glm::vec3 position;
  int seed;
  noise::module::Perlin* perlin;
public:
  HillChunkLoader(float, int, glm::vec3, int, noise::module::Perlin*);
  void Load(AbstractChunk *) override;
};
