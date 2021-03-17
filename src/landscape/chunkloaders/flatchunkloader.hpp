#pragma once

#include <base/location/chunkloader.hpp>

class FlatChunkLoader : public ChunkLoader {
public:
  FlatChunkLoader(float, int, glm::vec3);
  void Load(AbstractChunk *) override;
};
