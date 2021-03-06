#pragma once

#include "chunk.hpp"

class ChunkLoader;

class AbstractChunk : public Chunk {
private:
  ChunkLoader * chunk_loader;
  bool is_loaded;
public:
  AbstractChunk(Location * location, unsigned short x, unsigned short y, ChunkLoader * chunk_loader);

  virtual void LoadABS() override;

  void LoadTerrain(Terrain * terrain);
};
