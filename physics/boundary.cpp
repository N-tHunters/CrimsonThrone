#include "boundary.h"
#include <glm/glm.hpp>

BoundaryBox::BoundaryBox(float width, float height, float length) {
	this->width = width;
	this->height = height;
	this->length = length;
};

BoundaryCapsule::BoundaryCapsule(float height, float radius) {
	this->height = height;
	this->radius = radius;
};

BoundaryPlane::BoundaryPlane(float width, float height) {
	this->width = width;
	this->height = height;
};

BoundarySphere::BoundarySphere(float radius) {
	this->radius = radius;
};

bool BoundaryBox::Collide(Boundary* a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 e) {
	return false;
}

bool BoundaryPlane::Collide(Boundary* a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 e) {
	return false;
}

bool BoundaryCapsule::Collide(Boundary* a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 e) {
	return false;
}

bool BoundarySphere::Collide(Boundary* a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 e) {
	return false;
}

bool Boundary::Collide(Boundary* a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 e) {
	return false;
}