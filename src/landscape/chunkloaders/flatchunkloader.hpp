#pragma once

#include <base/location/chunkloader.hpp>

class FlatChunkLoader : public ChunkLoader {
  float size;
  int vertices_number;
  glm::vec3 position;
public:
  FlatChunkLoader(float, int, glm::vec3);
  void Load(AbstractChunk *) override;
};
