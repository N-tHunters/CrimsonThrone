#include "chunkloader.hpp"

void ChunkLoader::LoadEnd(std::vector<std::vector<float>> * height_map, AbstractChunk *chunk, GLuint texture1, GLuint texture2, std::vector<std::vector<float>> texture_map) {
  chunk->SetHeightMap(height_map, size, vertices_number, position, texture1, texture2, texture_map);
}

void ChunkLoader::Load(AbstractChunk *) {}

void ChunkLoader::LoadObjects(AbstractChunk *) {}
bool ChunkLoader::AreObjectsLoaded() { return true; }
