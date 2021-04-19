#include <landscape/biomeGenerator.hpp>

BiomeGenerator::BiomeGenerator(int seed, noise::module::Perlin* perlin) {
	this->seed = seed;
	this->perlin = perlin;
}

float BiomeGenerator::getBiome(float x, float y) {
	float value = perlin->GetValue(x / 100.0, y / 100.0, seed);
	/*if (value > -0.1f) {
		return 1;
	}
	return 0;*/
	value = value + 0.15 * 10.0;
	if (value > 1.0) {
		value = 1.0;
	} else if (value < 0.0) {
		value = 0.0;
	}

	return value;

}

float BiomeGenerator::getHeight(float x, float y) {
	float height = this->perlin->GetValue(x, y, this->seed) * 1000.0f;
	return height;
}