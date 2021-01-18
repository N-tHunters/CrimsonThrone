#include "boundary.h"
#include <iostream>
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

bool BoundaryBox::Collide(Boundary* other_boundary, glm::vec3 position_first, glm::vec3 rotation_first, glm::vec3 position_second, glm::vec3 rotation_second) {
	// return position_first.x >= position_second.x; 	
	bool a1 = position_first.x + this->width >= position_second.x - ((BoundaryBox*)other_boundary)->width;
	bool a2 = position_second.x + ((BoundaryBox*)other_boundary)->width >= position_first.x - this->width;

	bool b1 = position_first.y + this->height >= position_second.y - ((BoundaryBox*)other_boundary)->height;
	bool b2 = position_second.y + ((BoundaryBox*)other_boundary)->height >= position_first.y - this->height;

	bool c1 = position_first.z + this->length >= position_second.z - ((BoundaryBox*)other_boundary)->length;
	bool c2 = position_second.z + ((BoundaryBox*)other_boundary)->length >= position_first.z - this->length;
	return a1 && a2 && b1 && b2 && c1 && c2;
}

bool BoundaryPlane::Collide(Boundary* other_boundary, glm::vec3 position_first, glm::vec3 rotation_first, glm::vec3 position_second, glm::vec3 rotation_second) {
	return false;
}

bool BoundaryCapsule::Collide(Boundary* other_boundary, glm::vec3 position_first, glm::vec3 rotation_first, glm::vec3 position_second, glm::vec3 rotation_second) {
	return false;
}

bool BoundarySphere::Collide(Boundary* other_boundary, glm::vec3 position_first, glm::vec3 rotation_first, glm::vec3 position_second, glm::vec3 rotation_second) {
	return false;
}

bool Boundary::Collide(Boundary* other_boundary, glm::vec3 position_first, glm::vec3 rotation_first, glm::vec3 position_second, glm::vec3 rotation_second) {
	return false;
}