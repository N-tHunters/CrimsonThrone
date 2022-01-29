#pragma once

#include <base/location/chunkloader.hpp>

class FlatChunkLoader : public ChunkLoader {
  bool house;
public:
  FlatChunkLoader(float, int, glm::vec3);
  void LoadObjects(AbstractChunk* chunk) override;
  void Load(AbstractChunk *) override;
  bool AreObjectsLoaded() override;
};
