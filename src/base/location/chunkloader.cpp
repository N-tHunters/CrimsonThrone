#include "chunkloader.hpp"

void ChunkLoader::LoadEnd(std::vector<std::vector<float>> * height_map, AbstractChunk *chunk, GLuint texture1, GLuint texture2, GLuint blend_texture) {
  chunk->SetHeightMap(height_map, size, vertices_number, position, texture1, texture2, blend_texture);
}

void ChunkLoader::Load(AbstractChunk *) {}

void ChunkLoader::LoadObjects(AbstractChunk *) {}
bool ChunkLoader::AreObjectsLoaded() { return true; }
