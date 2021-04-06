#include <landscape/biomeGenerator.hpp>

BiomeGenerator::BiomeGenerator(int seed, noise::module::Perlin* perlin) {
	this->seed = seed;
	this->perlin = perlin;
}

int BiomeGenerator::getBiome(int x, int y) {
	float value = perlin->GetValue(x / 100.0, y / 100.0, seed);
	value += 1.0f;
	value = (value - 0.9) / 0.2f;
	printf("%f\n", value);
	if (value > 1.0f) {
		value = 1.0f;
	} else if (value < 0.0) {
		value = 0.0f;
	}

	return value;
}

float BiomeGenerator::getHeight(int x, int y) {
	float height = this->perlin->GetValue(x + this->seed % 65536, y + this->seed / 65536, 0.0f) * 1000.0f;
	return height;
}