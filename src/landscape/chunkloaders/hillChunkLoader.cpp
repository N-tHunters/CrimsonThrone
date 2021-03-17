#include "hillChunkLoader.hpp"

HillChunkLoader::HillChunkLoader(float size, int vertices_number, glm::vec3 position, int seed, noise::module::Perlin* perlin) {
	this->size = size;
	this->vertices_number = vertices_number;
	this->position = position;
	this->seed = seed;
	this->perlin = perlin;
}

void HillChunkLoader::Load(AbstractChunk * chunk) {
	std::vector<std::vector<float>> height_map;
	std::vector<float> v;
	for (int i = 0; i < vertices_number; i ++) {
		v.clear();
		for (int j = 0; j < vertices_number; j ++) {
			float x = chunk->GetX() * (vertices_number - 1) + i + seed % 65536;
			float y = chunk->GetY() * (vertices_number - 1) + j + seed / 65536;
			v.push_back(this->perlin->GetValue(x / 100.0, y / 100.0, 0.0) * 10.0);
		}
		height_map.push_back(v);
	}
	std::string texture_path;
	if (0 == 0) {
		texture_path = "resources/textures/grass.jpeg";
	} else {
		texture_path = "resources/textures/fire.png";
	}
	chunk->LoadTerrain(new Terrain(size, vertices_number, position, &height_map, texture_path, 10.0f));

	if (rand() % 10) {
		Model* tree_model = new Model("resources/models/tree.obj");
		float size = chunk->GetTerrain()->getSize();
		for (int i = 0; i < rand() % 100; i ++) {
			Mesh* tree_mesh = new Mesh("resources/textures/tree.png", tree_model, (rand() % 10 + 10) / 10.0f);
			glm::vec3 pos = chunk->GetTerrain()->getPosition() + glm::vec3((rand() % (int(size) * 10)) / 10.0f, 0.0f, (rand() % (int(size) * 10)) / 10.0f);
			pos.y = chunk->GetTerrain()->getHeight(pos);
			chunk->AddObj(new PhysicalObj(tree_mesh, false, true, false, false, pos, glm::vec3(0.0f, rand() % 360, 0.0f), "tree"));
		}
		delete tree_model;
	} else {
		Model* house_model = new Model("resources/models/house.obj");
		for (int i = 0; i < rand() % 5 + 3; i ++) {
			Mesh* house_mesh = new Mesh("resources/textures/house.png", house_model, 2.0f);
			glm::vec3 local_pos = glm::vec3((rand() % (int(size) * 10)) / 10.0f, 0.0f, (rand() % (int(size) * 10)) / 10.0f);
			glm::vec3 pos = chunk->GetTerrain()->getPosition() + local_pos;
			pos.y = chunk->GetTerrain()->getHeight(pos);
			chunk->AddObj(new PhysicalObj(house_mesh, false, true, false, false, pos, glm::vec3(0.0f, rand() % 360, 0.0f), "house"));
		}
		delete house_model;
	}
}