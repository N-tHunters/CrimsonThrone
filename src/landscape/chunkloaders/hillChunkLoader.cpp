#include "hillChunkLoader.hpp"

const int quote = 1;

HillChunkLoader::HillChunkLoader(float size, int vertices_number, glm::vec3 position, int seed, noise::module::Perlin* perlin, BiomeGenerator* biomeGenerator) {
	this->size = size;
	this->vertices_number = vertices_number;
	this->position = position;
	this->seed = seed;
	this->perlin = perlin;
	this->biomeGenerator = biomeGenerator;
}

void HillChunkLoader::Load(AbstractChunk * chunk) {
	std::vector<std::vector<float>> * height_map = new std::vector<std::vector<float>>();
	std::vector<float> v;

	float chunkX = chunk->GetX();
	float chunkY = chunk->GetY();
	float w = vertices_number - 1;

	std::vector<std::vector<float>> texture_map;
	std::vector<float> v2;

	for (int i = 0; i < vertices_number; i ++) {
		v.clear();
		v2.clear();
		for (int j = 0; j < vertices_number; j ++) {

			// float x = chunk->GetX() * (vertices_number - 1) + i + seed % 65536;
			// float y = chunk->GetY() * (vertices_number - 1) + j + seed / 65536;

			float x = chunkX + i / w;
			float y = chunkY + j / w;

			// float biome_height = biomeGenerator->getHeight(x / 100.0f, y / 100.0f);

			int biome = biomeGenerator->getBiome(x, y);

			float h = this->perlin->GetValue(x / 100.0, y / 100.0, seed);

			// printf("%f\n", h);

			v.push_back(h * 100.0f);
			// printf("%d\n", biome);
			v2.push_back(biome);
		}
		height_map->push_back(v);
		texture_map.push_back(v2);
	}

	GLuint texture1 = get_texture("grass");
	GLuint texture2 = get_texture("rock");

	LoadEnd(height_map, chunk, texture1, texture2, texture_map);
	// trees_num = rand() % 3 + 1;
	trees_num = 0;
}

void HillChunkLoader::LoadObjects(AbstractChunk *chunk) {
	Model* tree_model = get_model("tree");
	GLuint tree_texture = get_texture("tree");
	float size = chunk->GetTerrain()->getSize();
	int new_quote = quote;

	while (trees_num > 0 && new_quote > 0) {
		Mesh* tree_mesh = new Mesh(tree_model, (rand() % 10 + 10) / 10.0f, tree_texture);
		glm::vec3 pos = chunk->GetTerrain()->getPosition() + glm::vec3((rand() % (int(size) * 10)) / 10.0f, 0.0f, (rand() % (int(size) * 10)) / 10.0f);
		pos.y = chunk->GetTerrain()->getHeight(pos);
		chunk->AddObj(new PhysicalObj(tree_mesh, false, true, false, false, pos, glm::vec3(0.0f, rand() % 360, 0.0f), "tree"));

		trees_num--; new_quote--;
	}
	// delete tree_model;
}

bool HillChunkLoader::AreObjectsLoaded() {
	return trees_num == 0;
}
