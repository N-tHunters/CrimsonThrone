#include "flatgenerator.hpp"
#include <base/location/location.hpp>
#include <base/location/chunk.hpp>

FlatGenerator::FlatGenerator() {}

void FlatGenerator::Generate(Location * location, size_t width, size_t height, int chunk_width, int chunk_height, int vertices_number) {
  std::vector<std::vector<float>> height_map;
  std::vector<float> v;
  for (int i = 0; i < vertices_number; i ++) {
    v.clear();
    for (int j = 0; j < vertices_number; j ++) {
      v.push_back(0.0f);
    }
    height_map.push_back(v);
  }

  
  for(size_t i = 0; i < height; i++)
    for(size_t j = 0; j < width; j++) {
      Chunk * new_chunk = new Chunk(location, i, j, new Terrain((float)chunk_width, vertices_number, glm::vec3(chunk_width * i, 0.0f, chunk_height * j), &height_map));
      location->SetChunk(i, j, new_chunk);
    }
}
