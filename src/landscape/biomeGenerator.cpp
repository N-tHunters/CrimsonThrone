#include <landscape/biomeGenerator.hpp>

BiomeGenerator::BiomeGenerator(int seed, noise::module::Perlin* perlin) {
	this->seed = seed;
	this->perlin = perlin;
}

int BiomeGenerator::getBiome(int x, int y) {
	float value = perlin->GetValue(x / 100.0, y / 100.0, seed);
	if (value > 0.0f) {
		return 1;
	}

	return 0;

}

float BiomeGenerator::getHeight(int x, int y) {
	float height = this->perlin->GetValue(x + this->seed % 65536, y + this->seed / 65536, 0.0f) * 1000.0f;
	return height;
}