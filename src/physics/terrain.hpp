#ifndef TERRAIN_H
#define TERRAIN_H

#include <random>
#include <math.h>
#include <array>

#include "physicalObj.hpp"

#include "../render/shaderLoader.hpp"
#include "../render/camera.hpp"
#include "../render/shaderHolder.hpp"

#include "../math/vectors.hpp"

class Terrain {
	float size;
	float tile_width;
	int vertices_number;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;
	std::vector<std::vector<float>> height;
	PhysicalObj* obj;
	glm::vec3 position;
public:
	Terrain(float, int, glm::vec3);
	Terrain(Terrain&);

	glm::vec3 getPosition();
	float getHeight(glm::vec3);
	glm::vec3 getOutVector(glm::vec3);
	float getSize();
	PhysicalObj* getPhysicalObj();
	int getVerticesNumber();
	float getHeightMap(int x, int y);
	float getTileWidth();

	void draw(ShaderHolder*, Camera*, GLuint, GLuint);
};

#endif