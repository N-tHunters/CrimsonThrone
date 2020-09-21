#include "camera.h"

glm::vec3 Camera::getPosition() {
	return this->position;
}

glm::vec3 Camera::getRotation() {
	return this->rotation;
}

void Camera::setPosition(glm::vec3 newPosition) {
	this->position = newPosition;
}

void Camera::setRotation(glm::vec3 newRotation) {
	this->rotation = newRotation;
}

void Camera::changePosition(glm::vec3 deltaPosition) {
	this->position += deltaPosition;
}

void Camera::changeRotation(glm::vec3 deltaRotation) {
	this->rotation += deltaRotation;
}