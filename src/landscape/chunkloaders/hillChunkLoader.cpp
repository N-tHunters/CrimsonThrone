#include "hillChunkLoader.hpp"

const int quote = 100;

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

	for (int i = 0; i < vertices_number; i ++) {
		v.clear();
		for (int j = 0; j < vertices_number; j ++) {

			float x = chunkX + i / w;
			float y = chunkY + j / w;

			float h = this->perlin->GetValue(x / 100.0, y / 100.0, seed);

			v.push_back(h * 100.0f);
		}
		height_map->push_back(v);
	}

	std::vector<unsigned char> pixels;

	float pixel_count = 32.0f;

	for (float i = 0; i < pixel_count; i ++ ) {
		for (float j = 0; j < pixel_count; j ++) {
			float biome = biomeGenerator->getBiome(chunkX + i / pixel_count, chunkY + j / pixel_count);
			/*float h = this->perlin->GetValue((chunkX + i / pixel_count) / 100.0f, (chunkY + j / pixel_count) / 100.0, seed);
			char biome;
			if (h > 0.0) {
				biome = 1;
			} else {
				biome = 0;
			}*/
			pixels.push_back(std::round(biome * 255));
			pixels.push_back(0);
			pixels.push_back(0);
			pixels.push_back(255);
		}
	}

	// GLuint blend_texture = createTexture("resources/textures/rock.png");
	// GLuint blend_texture = get_texture("rock");

	GLuint texture1 = get_texture("grass2");
	GLuint texture2 = get_texture("grass2");

	LoadEnd(height_map, chunk, texture1, texture2, pixels);
	trees_num = 10;
}

void HillChunkLoader::LoadObjects(AbstractChunk *chunk) {
	Model* tree_model = get_model("tree");
	GLuint tree_texture = get_texture("tree");
	float size = chunk->GetTerrain()->getSize();
	int new_quote = quote;

	while (trees_num > 0 && new_quote > 0) {
	  Mesh* tree_mesh = new Mesh(tree_model, tree_texture, (rand() % 100 + 100) / 10.0f);
		glm::vec3 pos = chunk->GetTerrain()->getPosition() + glm::vec3((rand() % (int(size) * 10)) / 10.0f, 0.0f, (rand() % (int(size) * 10)) / 10.0f);
		pos.y = chunk->GetTerrain()->getHeight(pos);
		chunk->AddObj(new PhysicalObj(tree_mesh, false, true, false, false, pos, glm::vec3(0.0f, rand() % 360, 0.0f), "tree"));

		trees_num--; new_quote--;
	}
}

bool HillChunkLoader::AreObjectsLoaded() {
	return trees_num == 0;
}
