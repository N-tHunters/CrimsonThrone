#pragma once

#include <base/location/chunkloader.hpp>
#include <noise/noise.h>
#include <landscape/biomeGenerator.hpp>

class HillChunkLoader : public ChunkLoader {
	int seed;
  int trees_num;
	noise::module::Perlin* perlin;
	BiomeGenerator* biomeGenerator;
public:
	HillChunkLoader(float, int, glm::vec3, int, noise::module::Perlin*, BiomeGenerator*);
	void Load(AbstractChunk *) override;
  void LoadObjects(AbstractChunk *) override;
  bool AreObjectsLoaded() override;
};
