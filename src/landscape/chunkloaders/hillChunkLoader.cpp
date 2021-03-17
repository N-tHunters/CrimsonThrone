#include "hillChunkLoader.hpp"

HillChunkLoader::HillChunkLoader(float size, int vertices_number, glm::vec3 position, int seed, noise::module::Perlin* perlin) {
  this->size = size;
  this->vertices_number = vertices_number;
  this->position = position;
  this->seed = seed;
  this->perlin = perlin;
}

void HillChunkLoader::Load(AbstractChunk * chunk) {
  std::vector<std::vector<float>> * height_map;
  std::vector<float> v;
  for (int i = 0; i < vertices_number; i ++) {
    v.clear();
    for (int j = 0; j < vertices_number; j ++) {
      float x = chunk->GetX() * (vertices_number - 1) + i + seed % 65536;
      float y = chunk->GetY() * (vertices_number - 1) + j + seed / 65536;
      v.push_back(this->perlin->GetValue(x / 100.0, y / 100.0, 0.0) * 10.0);
    }
    height_map->push_back(v);
  }
  this->LoadEnd(height_map, chunk);
}
