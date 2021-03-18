#include <landscape/biomeGenerator.hpp>

BiomeGenerator::BiomeGenerator(int seed, noise::module::Perlin* perlin) {
	this->seed = seed;
	this->perlin = perlin;
}

int BiomeGenerator::getBiome(int x, int y) {
	if (x % 2 == y % 2)
		return 0;
	return 1;
}

float BiomeGenerator::getHeight(int x, int y) {
	float height = this->perlin->GetValue(x + this->seed % 65536, y + this->seed / 65536, 0.0f) * 1000.0f;
	return height;
}