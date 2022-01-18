#include "flatchunkloader.hpp"

FlatChunkLoader::FlatChunkLoader(float size, int vertices_number, glm::vec3 position) {
  this->size = size;
  this->vertices_number = vertices_number;
  this->position = position;
}

void FlatChunkLoader::Load(AbstractChunk * chunk) {
  std::vector<std::vector<float>> * height_map = new std::vector<std::vector<float>>();
  std::vector<float> v;

  for (int i = 0; i < vertices_number; i ++) {
    v.clear();
    for (int j = 0; j < vertices_number; j ++) {
      v.push_back(0.0f);
    }
    height_map->push_back(v);
  }

  std::vector<unsigned char> pixels;

  for (int i = 0; i < 32; i ++ ) {
    for (int j = 0; j < 32; j ++) {
      pixels.push_back(0);
      pixels.push_back(0);
      pixels.push_back(0);
    }
  }

  // GLuint blend_texture = createTexture(pixels, 32);

  GLuint texture1 = get_texture("grass");
  GLuint texture2 = get_texture("grass");

  LoadEnd(height_map, chunk, texture1, texture2, pixels);
}
