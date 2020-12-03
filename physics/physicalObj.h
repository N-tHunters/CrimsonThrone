#ifndef PHYSICALOBJ_H
#define PHYSICALOBJ_H

#include "../render/mesh.h"
//#include "physics/boundary.h"
#include <glm/glm.hpp>
#include "../render/camera.h"
#include "../render/shaderLoader.h"
#include "../render/shaderHolder.h"
//#include "terrain.h"

class Terrain;

class PhysicalObj {
	Mesh* mesh;
	bool isActive;
	bool isVisible;
	bool isTransparent;
	bool isFlying;
	glm::vec3 position;
	glm::vec3 rotation;
	bool onGround;
public:
	std::string name;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	PhysicalObj();
	PhysicalObj(glm::vec3);
	PhysicalObj(Mesh*, bool, bool, bool, bool, glm::vec3, glm::vec3, std::string);

	// Getters and setters for position and rotation

	glm::vec3 getPosition();
	float getPositionX();
	float getPositionY();
	float getPositionZ();

	glm::vec3 getRotation();
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

	std::string getName();

	virtual void update(float);
	void jump();
	void setSpeed(glm::vec2 speed);
	void setSpeed(glm::vec3 speed);
	void setOnGround(bool);
	bool getOnGround();
	float detectCollision(Terrain* terrain);
	void collideTerrain(Terrain*);

	void draw(ShaderHolder*, Camera*, GLuint, GLuint);
};

#endif
