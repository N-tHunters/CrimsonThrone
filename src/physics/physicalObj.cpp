#include "physicalObj.hpp"
#include "terrain.hpp"
#include <base/location/chunk.hpp>

PhysicalObj::PhysicalObj() {}

PhysicalObj::PhysicalObj(glm::vec3 position, BoundaryBox* boundary) {
	this->lastHeight = 0.0f;
	this->position = position;
	this->velocity = glm::vec3(0.0f);
	this->acceleration = glm::vec3(0.0f);
	this->force = glm::vec3(0.0f);
	this->onGround = true;
	this->mesh = nullptr;
	this->isActive = true;
	this->isVisible = true;
	this->isTransparent = false;
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
	this->boundary = new BoundaryBox(-glm::vec3(0.5f), glm::vec3(0.5f));
}

PhysicalObj::PhysicalObj(Mesh* mesh, bool isActive, bool isVisible, bool isTransparent, bool isFlying, glm::vec3 position, glm::vec3 rotation, const std::string& name, BoundaryBox* boundary) {
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
	if (this->isActive) {
		this->acceleration = this->force / this->mass;
		this->velocity += this->acceleration * dt;
		this->position += this->velocity * dt;
		this->force = glm::vec3(0.0f);
		if (this->onGround) {
			this->velocity.x /= 1.1f;
			this->velocity.z /= 1.1f;
		}
	}
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

std::string PhysicalObj::getName() { return name; }

void PhysicalObj::jump(Chunk* chunk) {
	if (isActive == false) {
		return;
	}
	if (velocity.y <= 0.0f) {
		bool t = false;
		for (int i = 0; i < chunk->GetObjsCount(); i++) {
			if (this->boundary->Collide(chunk->GetObj(i)->boundary, this->getPosition() - glm::vec3(0.0f, 0.5f, 0.0f), this->getRotation(), chunk->GetObj(i)->getPosition(), chunk->GetObj(i)->getRotation())) {
				t = true;
				break;
			}
		}
		if (this->detectCollision(chunk->GetTerrain()) > -1.0f) t = true;
		if (t) velocity.y = 20.0f;
	}
}

void PhysicalObj::jumpAnyway(Chunk* chunk) {
  velocity.y = 20.0f;
}

void PhysicalObj::setOnGround(bool value) { onGround = value; }

bool PhysicalObj::getOnGround() { return onGround; }

void PhysicalObj::setSpeed(glm::vec2 speed) {
	velocity.x = speed.x;
	velocity.z = speed.y;
}

void PhysicalObj::setSpeed(glm::vec3 speed) { velocity = speed; }

float PhysicalObj::detectCollision(Terrain* terrain) {
	return terrain->getHeight(getPosition()) - this->getPositionY() - reinterpret_cast<BoundaryBox*>(this->boundary)->getMin().y;
}

float PhysicalObj::detectCollision(Terrain* terrain, glm::vec3 position) {
	return terrain->getHeight(position) - position.y - reinterpret_cast<BoundaryBox*>(this->boundary)->getMin().y;
}

void PhysicalObj::collideTerrain(Terrain* terrain, float dt, Chunk* chunk_ptr) {
	if (isFlying) {
		return;
	}

	if (isActive == false) {
		return;
	}
	float height = this->detectCollision(terrain);
	float width = terrain->getTileWidth() / 2.0f;

	/*for (int i = 0; i < floor(b_width / width) + 1; i ++) {
		for (int j = 0; j < floor(b_length / width) + 1; j ++) {
			float x = this->position.x - (i - (ceil(b_width / width) + 1.0f) / 2.0f) * width;
			float y = this->position.y;
			float z = this->position.z - (j - (ceil(b_length / width) + 1.0f) / 2.0f) * width;
			float temp_height = this->detectCollision(terrain, glm::vec3(x, y, z));
			if (temp_height > height) {
				height = temp_height;
			}
		}
	}*/

	//height -= this->position.y;// + reinterpret_cast<BoundaryBox*>(this->boundary)->height / 2.0f;

	if (height > 0) {
		this->changePositionY(height);
		this->force.y = 0.0f;
		velocity.y = 0.0f;
		setOnGround(true);
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
	if (isActive == false || isTransparent == true || other_object->isTransparent == true) {
		return;
	}

	glm::vec3 this_velocity_x = glm::vec3(velocity.x * dt, 0.0f, 0.0f);
	glm::vec3 this_velocity_y = glm::vec3(0.0f, velocity.y * dt, 0.0f);
	glm::vec3 this_velocity_z = glm::vec3(0.0f, 0.0f, velocity.z * dt);

	glm::vec3 other_velocity_x = glm::vec3(other_object->velocity.x * dt, 0.0f, 0.0f);
	glm::vec3 other_velocity_y = glm::vec3(0.0f, other_object->velocity.y * dt, 0.0f);
	glm::vec3 other_velocity_z = glm::vec3(0.0f, 0.0f, other_object->velocity.z * dt);

	bool collided = false;

	if (this->boundary->Collide(static_cast<BoundaryBox*>(other_object->boundary),
			this->getPosition() + this_velocity_x,
			this->getRotation(),
			other_object->getPosition() + other_velocity_x,
			other_object->getRotation())) {
		this->velocity.x = 0.0f;
	}

	if (this->boundary->Collide(static_cast<BoundaryBox*>(other_object->boundary),
			this->getPosition() + this_velocity_y,
			this->getRotation(),
			other_object->getPosition() + other_velocity_y,
			other_object->getRotation())) {
		this->velocity.y = 0.0f;
		this->setOnGround(true);
	}

	if (this->boundary->Collide(static_cast<BoundaryBox*>(other_object->boundary),
			this->getPosition() + this_velocity_z,
			this->getRotation(),
			other_object->getPosition() + other_velocity_z,
			other_object->getRotation())) {
		this->velocity.z = 0.0f;
	}

	/*if (this->boundary->Collide(other_object->boundary, this->getPosition() + this_velocity_x, this->getRotation(), other_object->getPosition() + other_velocity_x, other_object->getRotation())) {
		if (this->boundary->Collide(other_object->boundary, this->getPosition() + glm::vec3(0, 1, 0) + this_velocity_x, this->getRotation(), other_object->getPosition() + other_velocity_z, other_object->getRotation()) || this_velocity_x.x == 0.0f)
		{
			this->velocity.x = 0.0f;
		} else {
			this->position.y += 0.5f;
		}
		//this->velocity.x = (this->position.x - other_object->getPositionX()) * 2.0f;
		//this->force.x = (this->position.x - other_object->getPositionX()) * 10.0f;
		collided = true;
		this->force.x = 0.0f;
		//other_object->velocity.x -= (this->position.x - other_object->getPositionX()) * 2.0f;
	}

	if (this->boundary->Collide(other_object->boundary, this->getPosition() + this_velocity_y, this->getRotation(), other_object->getPosition() + other_velocity_y, other_object->getRotation())) {
		this->velocity.y = 0.0f;
		this->force.y = 0.0f;
		collided = true;
	}

	if (this->boundary->Collide(other_object->boundary, this->getPosition() + this_velocity_z, this->getRotation(), other_object->getPosition() + other_velocity_z, other_object->getRotation())) {
		if (this->boundary->Collide(other_object->boundary, this->getPosition() + glm::vec3(0, 1, 0) + this_velocity_z, this->getRotation(), other_object->getPosition() + other_velocity_z, other_object->getRotation()) || this_velocity_z.z == 0.0f)
		{
			this->velocity.z = 0.0f;
		} else {
			this->position.y += 0.5f;
		}
		this->force.z = 0.0f;
		collided = true;
	}

	if (this->boundary->Collide(other_object->boundary,
	                            this->getPosition(),
	                            this->getRotation(),
	                            other_object->getPosition(),
	                            other_object->getRotation())) {
		if (other_object->isActive)
			other_object->force -= this->getPosition() - other_object->getPosition();
	}*/
}

Mesh* PhysicalObj::getMesh() {
	return this->mesh;
}