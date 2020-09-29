#ifndef PHYSICALOBJ_H
#define PHYSICALOBJ_H

#include "../render/mesh.h"
//#include "physics/boundary.h"
#include <glm/glm.hpp>
#include "../render/camera.h"
#include "../render/shaderLoader.h"

class PhysicalObj {
	Mesh mesh;
	bool isActive;
	bool isVisible;
	bool isTransparent;
	glm::vec3 position;
	glm::vec3 rotation;
public:
	string name;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	PhysicalObj();
	PhysicalObj(glm::vec3);
	PhysicalObj(Mesh, bool, bool, bool, glm::vec3, glm::vec3, string);
	glm::vec3 getRotation();
	float getPositionX();
	float getPositionY();
	float getPositionZ();

	glm::vec3 getPosition();
	float getRotationX();
	float getRotationY();
	float getRotationZ();

	void setPosition(glm::vec3);
	void setPositionX(float);
	void setPositionY(float);
	void setPositionZ(float);

	void setRotation(glm::vec3);
	void setRotationX(float);
	void setRotationY(float);
	void setRotationZ(float);

	void changePosition(glm::vec3);
	void changePositionX(float);
	void changePositionY(float);
	void changePositionZ(float);

	void changeRotation(glm::vec3);
	void changeRotationX(float);
	void changeRotationY(float);
	void changeRotationZ(float);

	void draw(Shader, Camera*);
	void update();

	string getName();
};

#endif