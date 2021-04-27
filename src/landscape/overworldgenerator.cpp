#include "overworldgenerator.hpp"
#include <base/location/location.hpp>
#include <base/location/chunk.hpp>
#include "chunkloaders/flatchunkloader.hpp"
#include "chunkloaders/hillChunkLoader.hpp"
#include <landscape/biomeGenerator.hpp>

OverWorldGenerator::OverWorldGenerator() {
  this->seed = rand();
}

void OverWorldGenerator::Generate(Location * location, size_t width, size_t height, int chunk_width, int chunk_height, int vertices_number) {

  noise::module::Perlin* perlin = new noise::module::Perlin();
  perlin->SetOctaveCount(8);

  // noise::module::Perlin* big_perlin = new noise::module::Perlin();
  // big_perlin->SetOctaveCount(4);
  // big_perlin->SetLacunarity(10.0f);

  BiomeGenerator* biomeGenerator = new BiomeGenerator(this->seed, perlin);

  std::vector<std::string> model_names = {
    "tree",
    "human"
  };

  std::vector<std::string> texture_names = {
    "tree",
    "grass",
    "rock",
    "icon"
  };

  load_models(model_names);
  load_textures(texture_names);

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      Chunk * new_chunk = new AbstractChunk(location, i, j, new HillChunkLoader((float)chunk_width, vertices_number, glm::vec3(chunk_width * i, 0.0f, chunk_height * j), this->seed, perlin, biomeGenerator));

      location->SetChunk(i, j, new_chunk);
    }
  }
}
