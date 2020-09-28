#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 rotation) {
	this->position = position;
	this->rotation = rotation;
}

glm::vec3 Camera::getPosition() {
	return this->position;
}

glm::vec3 Camera::getRotation() {
	return this->rotation;
}

void Camera::setPosition(glm::vec3 newPosition) {
	this->position = newPosition;
}

void Camera::setPositionX(float value) {
	this->position.x = value;
}

void Camera::setPositionY(float value) {
	this->position.y = value;
}

void Camera::setPositionZ(float value) {
	this->position.z = value;
}

void Camera::setRotation(glm::vec3 newRotation) {
	this->rotation = newRotation;
}

void Camera::setRotationX(float value) {
	this->rotation.x = value;
}

void Camera::setRotationY(float value) {
	this->rotation.y = value;
}

void Camera::setRotationZ(float value) {
	this->rotation.z = value;
}

void Camera::changePosition(glm::vec3 deltaPosition) {
	this->position += deltaPosition;
}

void Camera::changePositionX(float value) {
	this->position.x += value;
}

void Camera::changePositionY(float value) {
	this->position.y += value;
}

void Camera::changePositionZ(float value) {
	this->position.z += value;
}

void Camera::changeRotation(glm::vec3 deltaRotation) {
	this->rotation += deltaRotation;
}

void Camera::changeRotationX(float value) {
	this->rotation.x += value;
}

void Camera::changeRotationY(float value) {
	this->rotation.y += value;
}

void Camera::changeRotationZ(float value) {
	this->rotation.z += value;
}