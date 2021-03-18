#include "hillChunkLoader.hpp"

HillChunkLoader::HillChunkLoader(float size, int vertices_number, glm::vec3 position, int seed, noise::module::Perlin* perlin, BiomeGenerator* biomeGenerator) {
	this->size = size;
	this->vertices_number = vertices_number;
	this->position = position;
	this->seed = seed;
	this->perlin = perlin;
	this->biomeGenerator = biomeGenerator;
}

void HillChunkLoader::Load(AbstractChunk * chunk) {
  // printf("Hill Chunk loader thread started\n");
  std::vector<std::vector<float>> * height_map = new std::vector<std::vector<float>>();
	std::vector<float> v;

	for (int i = 0; i < vertices_number; i ++) {
		v.clear();
		for (int j = 0; j < vertices_number; j ++) {
			float x = chunk->GetX() * (vertices_number - 1) + i + seed % 65536;
			float y = chunk->GetY() * (vertices_number - 1) + j + seed / 65536;

			float biome_height = biomeGenerator->getHeight(x / 100.0f, y / 100.0f);
			
			v.push_back(this->perlin->GetValue(x / 100.0f, y / 100.0f, 0.0f) * 10.0f + biome_height);
		}
		height_map->push_back(v);
	}
	LoadEnd(height_map, chunk);
	/*
	int biome = biomeGenerator->getBiome(chunk->GetX(), chunk->GetY());

	std::string texture_path;

	if (biome == 0) {
		texture_path = "resources/textures/grass.jpeg";
	} else {
		texture_path = "resources/textures/wood.png";
	}

	chunk->LoadTerrain(new Terrain(size, vertices_number, position, &height_map, texture_path, 10.0f));

	if (biome == 0) {
		Model* tree_model = new Model("resources/models/tree.obj");
		float size = chunk->GetTerrain()->getSize();
		for (int i = 0; i < rand() % 100; i ++) {
			Mesh* tree_mesh = new Mesh("resources/textures/tree.png", tree_model, (rand() % 10 + 10) / 10.0f);
			glm::vec3 pos = chunk->GetTerrain()->getPosition() + glm::vec3((rand() % (int(size) * 10)) / 10.0f, 0.0f, (rand() % (int(size) * 10)) / 10.0f);
			pos.y = chunk->GetTerrain()->getHeight(pos);
			chunk->AddObj(new PhysicalObj(tree_mesh, false, true, false, false, pos, glm::vec3(0.0f, rand() % 360, 0.0f), "tree"));
		}
		delete tree_model;
	}*/
	// printf("Hill Thread chunk loader ended\n");
}
