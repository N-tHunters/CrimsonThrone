#include "chunkloader.hpp"

void ChunkLoader::LoadEnd(std::vector<std::vector<float>> * height_map, AbstractChunk *chunk) {
  chunk->SetHeightMap(height_map, size, vertices_number, position);
}

void ChunkLoader::Load(AbstractChunk *) {}
