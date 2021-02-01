#include "terrain.hpp"

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  size             The width of terrain in meters
 * @param[in]  vertices_number  The number of vertices
 * @param[in]  position         The position
 */
Terrain::Terrain(float size, int vertices_number, glm::vec3 position) {
	this->size = size;
	this->vertices_number = vertices_number;
	this->position = position;
	this->tile_width = size / (vertices_number - 1);

	std::vector<float> v;
	for (int i = 0; i < vertices_number; i ++) {
		v.clear();
		for (int j = 0; j < vertices_number; j ++) {
			float x = (i - vertices_number / 2) / 2.0f;
			float y = (j - vertices_number / 2) / 2.0f;
			v.push_back(cos(sqrt(x * x + y * y)) * 1.0);
		}
		this->height.push_back(v);
	}

	glm::vec3 normal;

	for (int i = 0; i < vertices_number - 1; i ++) {
		for (int j = 0; j < vertices_number - 1; j ++) {
			this->vertices.push_back(i * tile_width);
			this->vertices.push_back(this->height[i][j] * tile_width);
			this->vertices.push_back(j * tile_width);

			normal = -get_normal(glm::vec3(i, this->height[i][j], j),
								 glm::vec3(i + 1, this->height[i + 1][j], j),
								 glm::vec3(i, this->height[i][j + 1], j + 1));
			int c = 1;

			if (j > 0) {
				normal += -get_normal(glm::vec3(i, this->height[i][j - 1], j - 1),
									  glm::vec3(i + 1, this->height[i + 1][j - 1], j - 1),
									  glm::vec3(i, this->height[i][j], j));
				c += 1;
				normal += get_normal(glm::vec3(i + 1, this->height[i + 1][j], j),
									 glm::vec3(i + 1, this->height[i + 1][j - 1], j - 1),
									 glm::vec3(i, this->height[i][j], j));
				c += 1;
			}

			if (i > 0) {
				normal += -get_normal(glm::vec3(i, this->height[i][j], j),
									  glm::vec3(i + 1, this->height[i + 1][j], j),
									  glm::vec3(i, this->height[i][j + 1], j + 1));
				c += 1;
				normal += get_normal(glm::vec3(i + 1, this->height[i + 1][j + 1], j + 1),
									 glm::vec3(i + 1, this->height[i + 1][j], j),
									 glm::vec3(i, this->height[i][j + 1], j + 1));
				c += 1;
			}

			if (i > 0 && j > 0) {
				normal += get_normal(glm::vec3(i + 1, this->height[i][j], j),
								glm::vec3(i + 1, this->height[i][j - 1], j - 1),
								glm::vec3(i, this->height[i - 1][j], j));
				c += 1;
			}

			normal /= c;

			this->vertices.push_back(normal.x);
			this->vertices.push_back(normal.y);
			this->vertices.push_back(normal.z);

			this->vertices.push_back(0.0f);
			this->vertices.push_back(0.0f);

			this->vertices.push_back((i + 1) * tile_width);
			this->vertices.push_back(this->height[i + 1][j] * tile_width);
			this->vertices.push_back(j * tile_width);

			this->vertices.push_back(normal.x);
			this->vertices.push_back(normal.y);
			this->vertices.push_back(normal.z);

			this->vertices.push_back(1.0f);
			this->vertices.push_back(0.0f);

			this->vertices.push_back(i * tile_width);
			this->vertices.push_back(this->height[i][j + 1] * tile_width);
			this->vertices.push_back((j + 1) * tile_width);

			this->vertices.push_back(normal.x);
			this->vertices.push_back(normal.y);
			this->vertices.push_back(normal.z);

			this->vertices.push_back(0.0f);
			this->vertices.push_back(1.0f);

			this->indices.push_back(i * (vertices_number - 1) * 6 + j * 6);
			this->indices.push_back(i * (vertices_number - 1) * 6  + j * 6 + 1);
			this->indices.push_back(i * (vertices_number - 1) * 6  + j * 6 + 2);

			this->vertices.push_back((i + 1) * tile_width);
			this->vertices.push_back(this->height[i + 1][j] * tile_width);
			this->vertices.push_back(j * tile_width);

			normal = get_normal(glm::vec3(i + 1, this->height[i + 1][j + 1], j + 1),
								glm::vec3(i + 1, this->height[i + 1][j], j),
								glm::vec3(i, this->height[i][j + 1], j + 1));

			c = 1;

			if (j < vertices_number - 1) {
				normal += -get_normal(glm::vec3(i, this->height[i][j + 1], j + 1),
								 glm::vec3(i + 1, this->height[i + 1][j + 1], j + 1),
								 glm::vec3(i, this->height[i][j + 2], j + 2));
				c += 1;
				normal += get_normal(glm::vec3(i + 1, this->height[i + 1][j + 2], j + 2),
								glm::vec3(i + 1, this->height[i + 1][j + 1], j + 1),
								glm::vec3(i, this->height[i][j + 2], j + 2));
				c += 1;
			}

			/*if (i < vertices_number - 1) {
				normal += 
			}*/

			normal /= c;

			this->vertices.push_back(normal.x);
			this->vertices.push_back(normal.y);
			this->vertices.push_back(normal.z);

			this->vertices.push_back(1.0f);
			this->vertices.push_back(0.0f);

			this->vertices.push_back((i + 1) * tile_width);
			this->vertices.push_back(this->height[i + 1][j + 1] * tile_width);
			this->vertices.push_back((j + 1) * tile_width);

			this->vertices.push_back(normal.x);
			this->vertices.push_back(normal.y);
			this->vertices.push_back(normal.z);

			this->vertices.push_back(1.0f);
			this->vertices.push_back(1.0f);

			this->vertices.push_back(i * tile_width);
			this->vertices.push_back(this->height[i][j + 1] * tile_width);
			this->vertices.push_back((j + 1) * tile_width);

			this->vertices.push_back(normal.x);
			this->vertices.push_back(normal.y);
			this->vertices.push_back(normal.z);

			this->vertices.push_back(0.0f);
			this->vertices.push_back(1.0f);

			this->indices.push_back(i * (vertices_number - 1) * 6 + j * 6 + 3);
			this->indices.push_back(i * (vertices_number - 1) * 6  + j * 6 + 4);
			this->indices.push_back(i * (vertices_number - 1) * 6  + j * 6 + 5);
		}
	}
	this->obj = new PhysicalObj(new Mesh("resources/textures/rock.png", &(this->vertices), &(this->indices), 1), false, true, false, false, position, glm::vec3(0.0f, 0.0f, 0.0f), "terrain");
}

Terrain::Terrain(Terrain& terrain) {
	this->size = terrain.getSize();
	this->vertices_number = terrain.getVerticesNumber();
	this->position = terrain.getPosition();
	this->tile_width = terrain.getSize() / (terrain.getVerticesNumber() - 1);

	std::vector<float> v;
	for (int i = 0; i < terrain.getVerticesNumber(); i ++) {
		v.clear();
		for (int j = 0; j < terrain.getVerticesNumber(); j ++) {
			v.push_back(terrain.getHeightMap(i, j));
		}
		this->height.push_back(v);
	}
	this->obj = terrain.obj;
}

PhysicalObj* Terrain::getPhysicalObj() {
	return this->obj;
}

int Terrain::getVerticesNumber() {
	return this->vertices_number;
}

float Terrain::getHeightMap(int x, int y) {
	return this->height[x][y];
}

void Terrain::draw(ShaderHolder* shaderHolder, Camera* camera, GLuint width, GLuint height) {
	this->obj->draw(shaderHolder, camera, width, height);
}

glm::vec3 Terrain::getPosition() {
	return this->position;
}

float barrycentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

float Terrain::getHeight(glm::vec3 position) {
	float terrainX = position.x - this->position.x;
	float terrainY = position.z - this->position.z;
	float tileSize = this->tile_width;
	int tileX = floor(terrainX / tileSize);
	int tileY = floor(terrainY / tileSize);
	if (tileX >= this->vertices_number - 1 || tileY >= this->vertices_number - 1 || tileX < 0 || tileY < 0) {
		return -900.0f;
	}
	float xCoord = (terrainX - tileSize * tileX) / tileSize;
	float yCoord = (terrainY - tileSize * tileY) / tileSize;
	float answer;
	if (xCoord <= (1 - yCoord)) {
		answer = barrycentric(glm::vec3(0, this->height[tileX][tileY], 0),
							  glm::vec3(1, this->height[tileX + 1][tileY], 0),
							  glm::vec3(0, this->height[tileX][tileY + 1], 1),
							  glm::vec2(xCoord, yCoord));
	} else {
		answer = barrycentric(glm::vec3(1, this->height[tileX + 1][tileY], 0),
							  glm::vec3(1, this->height[tileX + 1][tileY + 1], 1),
							  glm::vec3(0, this->height[tileX][tileY + 1], 0),
							  glm::vec2(xCoord, yCoord));
	}
	return answer * this->tile_width + this->position.y;
}

glm::vec3 Terrain::getOutVector(glm::vec3 position) {
	float terrainX = position.x - this->position.x;
	float terrainY = position.z - this->position.z;
	float tileSize = this->tile_width;
	float tileX = floor(terrainX / tileSize);
	float tileY = floor(terrainY / tileSize);
	float xCoord = (terrainX - tileSize * tileX) / tileSize;
	float yCoord = (terrainY - tileSize * tileY) / tileSize;
	glm::vec3 answer;
	if (tileX >= this->size - 1 || tileY >= this->size - 1 || tileX < 0 || tileY < 0) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	if (xCoord <= (1 - yCoord)) {
		answer = get_normal(glm::vec3(0, this->height[tileX][tileY], 0),
							glm::vec3(1, this->height[tileX + 1][tileY], 0),
							glm::vec3(0, this->height[tileX][tileY + 1], 1));
	} else {
		answer = get_normal(glm::vec3(1, this->height[tileX + 1][tileY], 0),
							glm::vec3(1, this->height[tileX + 1][tileY + 1], 1),
							glm::vec3(0, this->height[tileX][tileY + 1], 0));
	}
	return answer;
	/*
	float h = (this->height[tileX][tileY] +
						this->height[tileX][tileY + 1] +
						this->height[tileX + 1][tileY] +
						this->height[tileX + 1][tileY + 1]) / 4.0f;
	glm::vec3 center = glm::vec3(this->tile_width / 2.0f, h, this->tile_width / 2.0f);
	return center - glm::vec3(xCoord, position.y, yCoord);*/
}

float Terrain::getSize() {
	return this->size;
}
