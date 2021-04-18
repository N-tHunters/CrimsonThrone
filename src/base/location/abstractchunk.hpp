#pragma once

#include "chunk.hpp"
#include <thread>
#include <render/textures.hpp>

class ChunkLoader;

class AbstractChunk : public Chunk {
private:
  ChunkLoader * chunk_loader;
  bool is_loaded;
  std::thread * loading_thread;
  unsigned short int load_state;
  std::vector<std::vector<float>> * height_map;
  float size;
  int vertices_number;
  glm::vec3 position;
  GLuint texture1, texture2;
  std::vector<unsigned char> blend_pixels;
public:
  AbstractChunk(Location * location, unsigned short x, unsigned short y, ChunkLoader * chunk_loader);

  virtual void LoadABS() override;

  void LoadTerrain(Terrain * terrain);
  bool IsLoaded() override;
  void SetLoaded();
  void SetHeightMap(std::vector<std::vector<float>> *,
                    float,
                    int,
                    glm::vec3,
                    GLuint texture1,
                    GLuint texture2,
                    std::vector<unsigned char> blend_pixels);
};
