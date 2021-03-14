#include "overworldgenerator.hpp"
#include <base/location/location.hpp>
#include <base/location/chunk.hpp>
#include "chunkloaders/hillChunkLoader.hpp"

OverWorldGenerator::OverWorldGenerator() {
  this->seed = rand();
}

void OverWorldGenerator::Generate(Location * location, size_t width, size_t height, int chunk_width, int chunk_height, int vertices_number) {

  noise::module::Perlin* perlin = new noise::module::Perlin();
  perlin->SetOctaveCount(4);

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      // Chunk * new_chunk = new Chunk(location, i, j, new Terrain((float)chunk_width, vertices_number, glm::vec3(chunk_width * i, 0.0f, chunk_height * j), &height_map, "resources/textures/grass.jpg"));
      Chunk * new_chunk = new AbstractChunk(location, i, j, new HillChunkLoader((float)chunk_width, vertices_number, glm::vec3(chunk_width * i, 0.0f, chunk_height * j), this->seed, perlin));
      location->SetChunk(i, j, new_chunk);
    }
  }
}