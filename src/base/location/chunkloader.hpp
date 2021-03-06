#pragma once

#include "abstractchunk.hpp"

class ChunkLoader {
private:
public:
  ChunkLoader() {}
  virtual void Load(AbstractChunk *) {}
};
