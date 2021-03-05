#include "overworldgenerator.hpp"
#include <base/location/location.hpp>
#include <base/location/chunk.hpp>

OverWorldGenerator::OverWorldGenerator() {}

void OverWorldGenerator::Generate(Location * location, size_t width, size_t height, int chunk_width, int chunk_height, int vertices_number) {
  std::vector<std::vector<float>> height_map;
  std::vector<float> v;

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      height_map.clear();
      for (int ii = 0; ii < vertices_number; ii ++) {
        v.clear();
        for (int jj = 0; jj < vertices_number; jj ++) {
          int x, y;
          x = ii + i * (vertices_number - 1);
          y = jj + j * (vertices_number - 1);
          v.push_back((cos(x) + sin(y)) / 2.0);
        }
        height_map.push_back(v);
      }
      Chunk * new_chunk = new Chunk(location, i, j, new Terrain((float)chunk_width, vertices_number, glm::vec3(chunk_width * i, 0.0f, chunk_height * j), &height_map, "resources/textures/grass.jpg"));
      location->SetChunk(i, j, new_chunk);
    }
  }
}