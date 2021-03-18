#pragma once

#include <base/location/chunkloader.hpp>
#include <noise/noise.h>
#include <landscape/biomeGenerator.hpp>

class HillChunkLoader : public ChunkLoader {
	float size;
	int vertices_number;
	glm::vec3 position;
	int seed;
	noise::module::Perlin* perlin;
	BiomeGenerator* biomeGenerator;
public:
	HillChunkLoader(float, int, glm::vec3, int, noise::module::Perlin*, BiomeGenerator*);
	void Load(AbstractChunk *m) override;
};