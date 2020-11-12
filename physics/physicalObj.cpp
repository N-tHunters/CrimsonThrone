#include "physicalObj.h"
#include "terrain.h"

PhysicalObj::PhysicalObj() {}

PhysicalObj::PhysicalObj(glm::vec3 position) {
	this->position = position;
	this->velocity = glm::vec3(0.0f);
	this->acceleration = glm::vec3(0.0f);
	this->onGround = true;
}

PhysicalObj::PhysicalObj(Mesh mesh, bool isActive, bool isVisible, bool isTransparent, glm::vec3 position, glm::vec3 rotation, string name) {
	this->name = name;
	this->mesh = mesh;
	this->position = position;
	this->rotation = rotation;
	//this->boundary = boundary;
	this->isActive = isActive;
	this->isVisible = isVisible;
	this->isTransparent = isTransparent;
	this->velocity = glm::vec3(0.0f);
	this->acceleration = glm::vec3(0.0f);
	this->mesh.init(this);
	this->onGround = true;
}

void PhysicalObj::draw(Shader* shader, Camera* camera, GLuint width, GLuint height) {
	if(this->isVisible) {
		this->mesh.draw(shader, camera, width, height);
	}
}

void PhysicalObj::update(float dt) {
	if(this->name == "Player" && this->velocity.y != 0.0f)
		printf("Vx: %f Vy: %f Vz: %f - %f %f %f - %f %f %f - %f\n", 
			this->velocity.x, this->velocity.y, this->velocity.z,
			this->acceleration.x, this->acceleration.y, this->acceleration.z,
			this->position.x, this->position.y, this->position.z, dt);
	this->position += this->velocity * dt;
	this->velocity += this->acceleration * dt;
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

void PhysicalObj::jump() {
	if(this->onGround) {
		this->velocity.y = 10.0f;
	}
}

void PhysicalObj::setOnGround(bool value) {
	this->onGround = value;
}

bool PhysicalObj::getOnGround() {
	return this->onGround;
}

void PhysicalObj::collideTerrain(Terrain* terrain, glm::vec2 movement, float VCAP) {

	float terrainHeight = terrain->getHeight(this->getPosition());

	float Xchange = movement.x;

	this->changePositionX(Xchange);

	if(this->getPosition().y < terrainHeight) {
		float diff = terrainHeight - this->getPosition().y;
		if(diff > VCAP) {
			this->changePositionY(diff * VCAP);
			this->acceleration.y = 0.0f;
			this->velocity.y = 0.0f;
			//this->changePositionX(-Xchange);
		} else {
			this->setPositionY(terrainHeight);
		}
		this->acceleration.y = 0.0f;
	} else if(this->getPosition().y > terrainHeight + 0.1) {
		this->acceleration.y = -G;
	} else {
		this->acceleration.y = 0;
	}

	float Ychange = movement.y;

	this->changePositionZ(Ychange);

	if(this->getPosition().y < terrainHeight) {
		float diff = terrainHeight - this->getPosition().y;
		if(diff > VCAP) {
			this->changePositionY(VCAP * diff);
			this->acceleration.y = 0.0f;
			this->velocity.y = 0.0f;
			//this->changePositionZ(-Ychange);
		} else {
			this->setPositionY(terrainHeight);
		}
		this->acceleration.y = 0.0f;
	} else if(this->getPosition().y > terrainHeight + 0.1) {
		this->acceleration.y = -G;
	} else {
		this->acceleration.y = 0;
	}

	terrainHeight = terrain->getHeight(this->getPosition());

	if(this->getPosition().y - 0.1f > terrainHeight) {
		this->setOnGround(false);
	} else {
		this->setOnGround(true);
	}
}