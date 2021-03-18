#pragma once

#include <noise/noise.h>
#include <cstdio>

class BiomeGenerator {
	int seed;
	noise::module::Perlin* perlin;
public:
	BiomeGenerator(int seed, noise::module::Perlin* perlin);
	int getBiome(int x, int y);
	float getHeight(int x, int y);
};