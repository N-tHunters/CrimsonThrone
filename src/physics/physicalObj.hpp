#ifndef PHYSICALOBJ_H
#define PHYSICALOBJ_H

#include "../render/mesh.hpp"
#include "boundary.hpp"
#include <glm/glm.hpp>
#include "../render/camera.hpp"
#include "../render/shaderLoader.hpp"
#include "../render/shaderHolder.hpp"
#include "../debug.hpp"

class Chunk;

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
	Boundary* boundary;
	float lastHeight;
	std::string name;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 force;
	float mass;
	PhysicalObj();
	PhysicalObj(glm::vec3, Boundary*);
	PhysicalObj(Mesh*, bool, bool, bool, bool, glm::vec3, glm::vec3, const std::string&);
	PhysicalObj(Mesh*, bool, bool, bool, bool, glm::vec3, glm::vec3, const std::string&, Boundary*);


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
	void jump(Chunk*);
	void setSpeed(glm::vec2 speed);
	void setSpeed(glm::vec3 speed);
	void setOnGround(bool);
	bool getOnGround();
	float detectCollision(Terrain* terrain);
	float detectCollision(Terrain* terrain, glm::vec3 position);
	void collideTerrain(Terrain*, float, Chunk*);
	Mesh* getMesh();

	void draw(ShaderHolder*, Camera*, GLuint, GLuint);

	void collide(PhysicalObj*, float, glm::vec3, bool);
};

#endif
