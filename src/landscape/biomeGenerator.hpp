#pragma once

#include <noise/noise.h>
#include <cstdio>

class BiomeGenerator {
	int seed;
	noise::module::Perlin* perlin;
public:
	BiomeGenerator(int seed, noise::module::Perlin* perlin);
	float getBiome(float x, float y);
	float getHeight(float x, float y);
};