#include "chunkloader.hpp"

void ChunkLoader::LoadEnd(std::vector<std::vector<float>> * height_map, AbstractChunk *chunk) {
  chunk->LoadTerrain(new Terrain(size, vertices_number, position, height_map, 10.0f));
  chunk->SetLoaded();
}

void ChunkLoader::Load(AbstractChunk *) {}
