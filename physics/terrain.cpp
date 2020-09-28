#include "terrain.h"
#include <random>
#include <math.h>

Terrain::Terrain(int size, float scale) {
	this->size = size;
	this->scale = scale;
	std::vector<float> v;
	for(int i = 0; i < size; i ++) {
		v.clear();
		for(int j = 0; j < size; j ++) {
			v.push_back((float)(rand() % 3000 - 1000) / 3000.0f);
			//v.push_back(0.0f);
		}
		this->height.push_back(v);
	}

	for(int i = 0; i < size - 1; i ++) {
		for(int j = 0; j < size - 1; j ++) {
			this->vertices.push_back((i - size / 2 + 0.5) * scale);
			this->vertices.push_back(this->height[i][j] * scale);
			this->vertices.push_back((j - size / 2 + 0.5) * scale);

			this->vertices.push_back(0.0f);
			this->vertices.push_back(0.0f);

			this->vertices.push_back((i + 1 - size / 2 + 0.5) * scale);
			this->vertices.push_back(this->height[i + 1][j] * scale);
			this->vertices.push_back((j - size / 2 + 0.5) * scale);

			this->vertices.push_back(1.0f);
			this->vertices.push_back(0.0f);

			this->vertices.push_back((i - size / 2 + 0.5) * scale);
			this->vertices.push_back(this->height[i][j + 1] * scale);
			this->vertices.push_back((j + 1 - size / 2 + 0.5) * scale);

			this->vertices.push_back(0.0f);
			this->vertices.push_back(1.0f);

			this->indices.push_back(i * (size - 1) * 6 + j * 6);
			this->indices.push_back(i * (size - 1) * 6  + j * 6 + 1);
			this->indices.push_back(i * (size - 1) * 6  + j * 6 + 2);

			// Arthur wanted this

			this->vertices.push_back((i + 1 - size / 2 + 0.5) * scale);
			this->vertices.push_back(this->height[i + 1][j] * scale);
			this->vertices.push_back((j - size / 2 + 0.5) * scale);

			this->vertices.push_back(1.0f);
			this->vertices.push_back(0.0f);

			this->vertices.push_back((i + 1 - size / 2 + 0.5) * scale);
			this->vertices.push_back(this->height[i + 1][j + 1] * scale);
			this->vertices.push_back((j + 1 - size / 2 + 0.5) * scale);

			this->vertices.push_back(1.0f);
			this->vertices.push_back(1.0f);

			this->vertices.push_back((i - size / 2 + 0.5) * scale);
			this->vertices.push_back(this->height[i][j + 1] * scale);
			this->vertices.push_back((j + 1 - size / 2 + 0.5) * scale);

			this->vertices.push_back(0.0f);
			this->vertices.push_back(1.0f);

			this->indices.push_back(i * (size - 1) * 6 + j * 6 + 3);
			this->indices.push_back(i * (size - 1) * 6  + j * 6 + 4);
			this->indices.push_back(i * (size - 1) * 6  + j * 6 + 5);
		}
	}
	this->obj = new PhysicalObj(Mesh("resources/textures/rock.png", this->vertices, this->indices), false, true, false, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), "terrain");
}

void Terrain::draw(Shader shader, Camera* camera) {
	this->obj->draw(shader, camera);
}

float Terrain::getHeight(glm::vec3 position) {
	float terrainX = position.x - this->obj->getPositionX();
	float terrainY = position.z - this->obj->getPositionZ();
	float tileSize = this->scale / (this->size - 1);
	float tileX = floor(terrainX / tileSize);
	float tileY = floor(terrainY / tileSize);
	if(tileX >= this->size - 1 || tileY >= this->size - 1 || tileX < 0 || tileY < 0) {
		return 0.0f;
		printf("ji\n");
	} else {
		return 1.0;
	}
}