#include "physicalObj.hpp"
#include "terrain.hpp"
#include "../base/chunk.h"

PhysicalObj::PhysicalObj() {}

PhysicalObj::PhysicalObj(glm::vec3 position, Boundary* boundary) {
	this->lastHeight = 0.0f;
	this->position = position;
	this->velocity = glm::vec3(0.0f);
	this->acceleration = glm::vec3(0.0f);
	this->force = glm::vec3(0.0f);
	this->onGround = true;
	this->mesh = nullptr;
	this->isActive = true;
	this->isVisible = true;
	this->isTransparent = true;
	this->isFlying = false;
	this->boundary = boundary;
	this->mass = 1.0f;
}

PhysicalObj::PhysicalObj(Mesh* mesh, bool isActive, bool isVisible, bool isTransparent, bool isFlying, glm::vec3 position, glm::vec3 rotation, const std::string& name) {
	this->lastHeight = 0.0f;
	this->name = name;
	this->mesh = mesh;
	this->position = position;
	this->rotation = rotation;
	this->isActive = isActive;
	this->isVisible = isVisible;
	this->isTransparent = isTransparent;
	this->isFlying = isFlying;
	this->velocity = glm::vec3(0.0f);
	this->acceleration = glm::vec3(0.0f);
	this->force = glm::vec3(0.0f);
	this->mesh->init(this);
	this->onGround = true;
	this->mass = 1.0f;
}

PhysicalObj::PhysicalObj(Mesh* mesh, bool isActive, bool isVisible, bool isTransparent, bool isFlying, glm::vec3 position, glm::vec3 rotation, const std::string& name, Boundary* boundary) {
	this->lastHeight = 0.0f;
	this->name = name;
	this->mesh = mesh;
	this->position = position;
	this->rotation = rotation;
	this->isActive = isActive;
	this->isVisible = isVisible;
	this->isTransparent = isTransparent;
	this->isFlying = isFlying;
	this->velocity = glm::vec3(0.0f);
	this->acceleration = glm::vec3(0.0f);
	this->force = glm::vec3(0.0f);
	this->mesh->init(this);
	this->onGround = true;
	this->boundary = boundary;
	this->mass = 1.0f;
}

void PhysicalObj::draw(ShaderHolder* shaderHolder, Camera* camera, GLuint width, GLuint height) {
	if (this->isVisible) {
		this->mesh->draw(shaderHolder, camera, width, height);
	}
}

void PhysicalObj::update(float dt) {
	this->acceleration = this->force / this->mass;
	this->velocity += this->acceleration * dt;
	this->position += this->velocity * dt;
	this->force = glm::vec3(0.0f);
}

glm::vec3 PhysicalObj::getPosition() {
	return this->position;
}

float PhysicalObj::getPositionX() {
	return this->position.x;
}

float PhysicalObj::getPositionY() {
	return this->position.y;
}

float PhysicalObj::getPositionZ() {
	return this->position.z;
}

glm::vec3 PhysicalObj::getRotation() {
	return this->rotation;
}

float PhysicalObj::getRotationX() {
	return this->rotation.x;
}

float PhysicalObj::getRotationY() {
	return this->rotation.y;
}

float PhysicalObj::getRotationZ() {
	return this->rotation.z;
}

void PhysicalObj::setPosition(glm::vec3 position) {
	this->position = position;
}

void PhysicalObj::setPositionX(float value) {
	this->position.x = value;
}

void PhysicalObj::setPositionY(float value) {
	this->position.y = value;
}

void PhysicalObj::setPositionZ(float value) {
	this->position.z = value;
}

void PhysicalObj::setRotation(glm::vec3 rotation) {
	this->rotation = rotation;
}

void PhysicalObj::setRotationX(float value) {
	this->rotation.x = value;
}

void PhysicalObj::setRotationY(float value) {
	this->rotation.y = value;
}

void PhysicalObj::setRotationZ(float value) {
	this->rotation.z = value;
}

void PhysicalObj::changePosition(glm::vec3 delta) {
	this->position += delta;
}

void PhysicalObj::changePositionX(float delta) {
	this->position.x += delta;
}

void PhysicalObj::changePositionY(float delta) {
	this->position.y += delta;
}

void PhysicalObj::changePositionZ(float delta) {
	this->position.z += delta;
}

void PhysicalObj::changeRotation(glm::vec3 delta) {
	this->rotation += delta;
}

void PhysicalObj::changeRotationX(float delta) {
	this->rotation.x += delta;
}

void PhysicalObj::changeRotationY(float delta) {
	this->rotation.y += delta;
}

void PhysicalObj::changeRotationZ(float delta) {
	this->rotation.z += delta;
}

string PhysicalObj::getName() {
	return this->name;
}

void PhysicalObj::jump(Chunk* chunk) {
	if (abs(velocity.y) < 1.0f) {
		bool t = false;
		for (int i = 0; i < chunk->GetObjsCount(); i++) {
			if (this->boundary->Collide(chunk->GetObj(i)->boundary, this->getPosition() - glm::vec3(0.0f, 0.5f, 0.0f), this->getRotation(), chunk->GetObj(i)->getPosition(), chunk->GetObj(i)->getRotation())) {
				t = true;
				break;
			}
		}
		if (this->detectCollision(chunk->GetTerrain()) > -1.0f) {
			t = true;
		}
		if (t) {
			velocity.y = 10.0f;
		}
	}
}

void PhysicalObj::setOnGround(bool value) {
	this->onGround = value;
}

bool PhysicalObj::getOnGround() {
	return this->onGround;
}

void PhysicalObj::setSpeed(glm::vec2 speed) {
	velocity.x = speed.x;
	velocity.z = speed.y;
}

void PhysicalObj::setSpeed(glm::vec3 speed) {
	velocity = speed;
}

float PhysicalObj::detectCollision(Terrain* terrain) {
	return terrain->getHeight(this->getPosition()) - this->getPositionY();
}

void PhysicalObj::collideTerrain(Terrain* terrain, float dt, Chunk* chunk_ptr) {
	float height = this->detectCollision(terrain);
	if (height > 0) {
		this->setPositionY(terrain->getHeight(this->getPosition()));
		this->force.y = 0.0f;
		velocity.y = 0.0f;
		this->setOnGround(true);
	} else if (height > -0.1f) {
		this->setOnGround(true);
		this->force.y = 0.0f;
	} else {
		bool t = false;
		for (int i = 0; i < chunk_ptr->GetObjsCount(); i++) {
			if (this == chunk_ptr->GetObj(i)) {
				continue;
			}
			if (this->boundary->Collide(chunk_ptr->GetObj(i)->boundary, this->getPosition() - glm::vec3(0.0f, 0.5f, 0.0f), this->getRotation(), chunk_ptr->GetObj(i)->getPosition(), chunk_ptr->GetObj(i)->getRotation())) {
				t = true;
				break;
			}
		}
		if (!t) {
			this->setOnGround(false);
			this->force.y = -G * this->mass;
		}
	}
}

void PhysicalObj::collide(PhysicalObj* other_object, float dt, glm::vec3 velocity, bool isPlayer) {
	glm::vec3 this_velocity_x = glm::vec3(velocity.x * dt, 0.0f, 0.0f);
	glm::vec3 this_velocity_y = glm::vec3(0.0f, velocity.y * dt, 0.0f);
	glm::vec3 this_velocity_z = glm::vec3(0.0f, 0.0f, velocity.z * dt);

	glm::vec3 other_velocity_x = glm::vec3(other_object->velocity.x * dt, 0.0f, 0.0f);
	glm::vec3 other_velocity_y = glm::vec3(0.0f, other_object->velocity.y * dt, 0.0f);
	glm::vec3 other_velocity_z = glm::vec3(0.0f, 0.0f, other_object->velocity.z * dt);

	// glm::vec3 result = glm::vec3(1.0f, 1.0f, 1.0f);

	bool collided = false;

	if (this->boundary->Collide(other_object->boundary, this->getPosition() + this_velocity_x, this->getRotation(), other_object->getPosition() + other_velocity_x, other_object->getRotation())) {
		this->velocity.x = 0.0f;
		this->force.x = 0.0f;
		collided = true;
	}

	if (this->boundary->Collide(other_object->boundary, this->getPosition() + this_velocity_y, this->getRotation(), other_object->getPosition() + other_velocity_y, other_object->getRotation())) {
		this->velocity.y = 0.0f;
		this->force.y = 0.0f;
		collided = true;
	}

	if (this->boundary->Collide(other_object->boundary, this->getPosition() + this_velocity_z, this->getRotation(), other_object->getPosition() + other_velocity_z, other_object->getRotation())) {
		this->velocity.z = 0.0f;
		this->force.z = 0.0f;
		collided = true;
	}


	if (isPlayer) {
		if (collided)
		{
			other_object->getMesh()->changeTexture("resources/textures/fire.png");
			other_object->getMesh()->activeDebug = true;
		} else if (other_object->getMesh()->activeDebug) {
			other_object->getMesh()->activeDebug = false;
			other_object->getMesh()->changeTexture("resources/textures/box.jpeg");
		}
	}

	// return result;
}

Mesh* PhysicalObj::getMesh() {
	return this->mesh;
}