#include "flatchunkloader.hpp"

FlatChunkLoader::FlatChunkLoader(float size, int vertices_number, glm::vec3 position) {
  this->size = size;
  this->vertices_number = vertices_number;
  this->position = position;
}

void FlatChunkLoader::Load(AbstractChunk * chunk) {
  std::vector<std::vector<float>> * height_map = new std::vector<std::vector<float>>();
  std::vector<float> v;

  std::vector<std::vector<float>> texture_map;

  for (int i = 0; i < vertices_number; i ++) {
    v.clear();
    for (int j = 0; j < vertices_number; j ++) {
      v.push_back(0.0f);
    }
    height_map->push_back(v);
    texture_map.push_back(v);
  }

  GLuint texture1 = get_texture("grass");
  GLuint texture2 = get_texture("grass");

  LoadEnd(height_map, chunk, texture1, texture2, texture_map);
}
