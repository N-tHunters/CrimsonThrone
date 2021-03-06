#include "flatgenerator.hpp"
#include <base/location/location.hpp>
#include <base/location/chunk.hpp>
#include "chunkloaders/flatchunkloader.hpp"
#include <base/location/abstractchunk.hpp>

FlatGenerator::FlatGenerator() {}

void FlatGenerator::Generate(Location * location, size_t width, size_t height, int chunk_width, int chunk_height, int vertices_number) {
  for(size_t i = 0; i < height; i++)
    for(size_t j = 0; j < width; j++) {
      Chunk * new_chunk = new AbstractChunk(location, i, j, new FlatChunkLoader((float)chunk_width, vertices_number, glm::vec3(chunk_width * i, 0.0f, chunk_height * j)));

      location->SetChunk(i, j, new_chunk);
    }
}
