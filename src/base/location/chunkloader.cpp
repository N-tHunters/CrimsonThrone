#include "chunkloader.hpp"

void ChunkLoader::LoadEnd(std::vector<std::vector<float>> * height_map, AbstractChunk *chunk, GLuint texture1, GLuint texture2, std::vector<unsigned char> blend_pixels) {
  chunk->SetHeightMap(height_map, size, vertices_number, position, texture1, texture2, blend_pixels);
}

void ChunkLoader::Load(AbstractChunk *) {}

void ChunkLoader::LoadObjects(AbstractChunk *) {}
bool ChunkLoader::AreObjectsLoaded() { return true; }
