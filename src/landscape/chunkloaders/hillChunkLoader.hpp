#pragma once

#include <base/location/chunkloader.hpp>
#include <noise/noise.h>

class HillChunkLoader : public ChunkLoader {
  int seed;
  noise::module::Perlin* perlin;
public:
  HillChunkLoader(float, int, glm::vec3, int, noise::module::Perlin*);
  void Load(AbstractChunk *) override;
};
