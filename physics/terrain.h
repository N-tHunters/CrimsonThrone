#include "physicalObj.h"
#include "../render/shaderLoader.h"
#include "../render/camera.h"

class Terrain {
	int size;
	float scale = scale;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;
	std::vector<std::vector<float>> height;
	PhysicalObj* obj;
public:
	Terrain(int, float);
	void draw(Shader, Camera*);
	float getHeight(glm::vec3);
};