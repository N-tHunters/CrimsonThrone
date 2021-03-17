#pragma once

#include "abstractchunk.hpp"


class ChunkLoader {
protected:
  float size;
  int vertices_number;
  glm::vec3 position;
public:
  ChunkLoader() {}
  virtual void Load(AbstractChunk *); // Need to be called as a thread
  void LoadEnd(std::vector<std::vector<float>> * height_map, AbstractChunk * chunk); // This is called in the end
};
