#include "physicalObj.hpp"
#include "terrain.hpp"
#include "../base/chunk.hpp"

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
	if (this->isVisible) this->mesh->draw(shaderHolder, camera, width, height);
}

void PhysicalObj::update(float dt) {
	acceleration = force / mass;
	velocity += acceleration * dt;
	position += velocity * dt;
}

glm::vec3 PhysicalObj::getPosition() { return position; }

float PhysicalObj::getPositionX() { return position.x; }

float PhysicalObj::getPositionY() { return position.y; }

float PhysicalObj::getPositionZ() { return position.z; }

glm::vec3 PhysicalObj::getRotation() { return rotation; }

float PhysicalObj::getRotationX() { return rotation.x; }

float PhysicalObj::getRotationY() { return rotation.y; }

float PhysicalObj::getRotationZ() { return rotation.z; }

void PhysicalObj::setPosition(glm::vec3 position) { this->position = position; }

void PhysicalObj::setPositionX(float value) { position.x = value; }

void PhysicalObj::setPositionY(float value) { position.y = value; }

void PhysicalObj::setPositionZ(float value) { position.z = value; }

void PhysicalObj::setRotation(glm::vec3 rotation) { this->rotation = rotation; }

void PhysicalObj::setRotationX(float value) { rotation.x = value; }

void PhysicalObj::setRotationY(float value) { rotation.y = value; }

void PhysicalObj::setRotationZ(float value) { rotation.z = value; }

void PhysicalObj::changePosition(glm::vec3 delta) { position += delta; }

void PhysicalObj::changePositionX(float delta) { position.x += delta; }

void PhysicalObj::changePositionY(float delta) { position.y += delta; }

void PhysicalObj::changePositionZ(float delta) { position.z += delta; }

void PhysicalObj::changeRotation(glm::vec3 delta) { rotation += delta; }

void PhysicalObj::changeRotationX(float delta) { rotation.x += delta; }

void PhysicalObj::changeRotationY(float delta) { rotation.y += delta; }

void PhysicalObj::changeRotationZ(float delta) { rotation.z += delta; }

string PhysicalObj::getName() { return name; }

void PhysicalObj::jump(Chunk* chunk) {
	if (abs(velocity.y) < 1.0f) {
		bool t = false;
		for (int i = 0; i < chunk->GetObjsCount(); i++) {
			if (this->boundary->Collide(chunk->GetObj(i)->boundary, this->getPosition() - glm::vec3(0.0f, 0.5f, 0.0f), this->getRotation(), chunk->GetObj(i)->getPosition(), chunk->GetObj(i)->getRotation())) {
				t = true;
				break;
			}
		}
		if (this->detectCollision(chunk->GetTerrain()) > -1.0f) t = true;
		if (t) velocity.y = 10.0f;
	}
}

void PhysicalObj::setOnGround(bool value) { onGround = value; }

bool PhysicalObj::getOnGround() { return onGround; }

void PhysicalObj::setSpeed(glm::vec2 speed) {
	velocity.x = speed.x;
	velocity.z = speed.y;
}

void PhysicalObj::setSpeed(glm::vec3 speed) { velocity = speed; }

float PhysicalObj::detectCollision(Terrain* terrain) {
	return terrain->getHeight(getPosition()) - getPositionY();
}

void PhysicalObj::collideTerrain(Terrain* terrain, float dt) {
	float height = detectCollision(terrain);
	if (height > 0) {
		setPositionY(terrain->getHeight(getPosition()));
		acceleration.y = 0.0f;
		velocity.y = 0.0f;
		setOnGround(true);
	} else if (height > -0.1f) {
		setOnGround(true);
		acceleration.y = 0.0f;
	} else {
		setOnGround(false);
		acceleration.y = -G;
	}
}

glm::vec3 PhysicalObj::collide(PhysicalObj* other_object, float dt, glm::vec3 velocity) {
	glm::vec3 this_velocity_x = glm::vec3(velocity.x * dt, 0.0f, 0.0f);
	glm::vec3 this_velocity_y = glm::vec3(0.0f, velocity.y * dt, 0.0f);
	glm::vec3 this_velocity_z = glm::vec3(0.0f, 0.0f, velocity.z * dt);

	glm::vec3 other_velocity_x = glm::vec3(other_object->velocity.x * dt, 0.0f, 0.0f);
	glm::vec3 other_velocity_y = glm::vec3(0.0f, other_object->velocity.y * dt, 0.0f);
	glm::vec3 other_velocity_z = glm::vec3(0.0f, 0.0f, other_object->velocity.z * dt);

	glm::vec3 result = glm::vec3(1.0f, 1.0f, 1.0f);

	if (boundary->Collide(other_object->boundary, getPosition() + this_velocity_x, getRotation(), other_object->getPosition() + other_velocity_x, other_object->getRotation()))
		result.x = 0.0f;

	if (boundary->Collide(other_object->boundary, getPosition() + this_velocity_y, getRotation(), other_object->getPosition() + other_velocity_y, other_object->getRotation()))
		result.y = 0.0f;

	if (boundary->Collide(other_object->boundary, getPosition() + this_velocity_z, getRotation(), other_object->getPosition() + other_velocity_z, other_object->getRotation()))
		result.z = 0.0f;

	if (result.x + result.y + result.z < 3.0f) {
	  //		this->velocity = (this->getPosition() - other_object->getPosition()) * 0.1f;
	  //	result = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	return result;
}
