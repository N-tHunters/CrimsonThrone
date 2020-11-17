#ifndef TERRAIN_H
#define TERRAIN_H

#include "physicalObj.h"
#include "../render/shaderLoader.h"
#include "../render/camera.h"
#include "../render/shaderHolder.h"

class Terrain {
	int size;
	float scale = scale;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;
	std::vector<std::vector<float>> height;
	PhysicalObj* obj;
public:
	Terrain(int, float);
	void draw(ShaderHolder*, Camera*, GLuint, GLuint);
	float getHeight(glm::vec3);
};

#endif