#ifndef TERRAIN_H
#define TERRAIN_H

#include "physicalObj.h"
#include "../render/shaderLoader.h"
#include "../render/camera.h"
#include "../render/shaderHolder.h"

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
	glm::vec3 getPosition();
	void draw(ShaderHolder*, Camera*, GLuint, GLuint);
	float getHeight(glm::vec3);
};

#endif