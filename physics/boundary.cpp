#include "boundary.hpp"
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

bool BoundaryBox::Collide(Boundary* other_boundary,
                          glm::vec3 position_of_first_object,
                          glm::vec3 rotation_of_first_object,
                          glm::vec3 position_of_second_object,
                          glm::vec3 rotation_of_second_object) {
	bool a1 = position_of_first_object.x + this->width >=
	          position_of_second_object.x - reinterpret_cast<BoundaryBox*>(other_boundary)->width;

	bool a2 = position_of_second_object.x + reinterpret_cast<BoundaryBox*>(other_boundary)->width >=
	          position_of_first_object.x - this->width;

	bool b1 = position_of_first_object.y + this->height >=
	          position_of_second_object.y - reinterpret_cast<BoundaryBox*>(other_boundary)->height;

	bool b2 = position_of_second_object.y + reinterpret_cast<BoundaryBox*>(other_boundary)->height >=
	          position_of_first_object.y - this->height;

	bool c1 = position_of_first_object.z + this->length >=
	          position_of_second_object.z - reinterpret_cast<BoundaryBox*>(other_boundary)->length;

	bool c2 = position_of_second_object.z + reinterpret_cast<BoundaryBox*>(other_boundary)->length >=
	          position_of_first_object.z - this->length;

	return a1 && a2 && b1 && b2 && c1 && c2;
}

bool BoundaryPlane::Collide(Boundary* other_boundary,
                            glm::vec3 position_of_first_object,
                            glm::vec3 rotation_of_first_object,
                            glm::vec3 position_of_second_object,
                            glm::vec3 rotation_of_second_object) {
	return false;
}

bool BoundaryCapsule::Collide(Boundary* other_boundary,
                              glm::vec3 position_of_first_object,
                              glm::vec3 rotation_of_first_object,
                              glm::vec3 position_of_second_object,
                              glm::vec3 rotation_of_second_object) {
	return false;
}

bool BoundarySphere::Collide(Boundary* other_boundary,
                             glm::vec3 position_of_first_object,
                             glm::vec3 rotation_of_first_object,
                             glm::vec3 position_of_second_object,
                             glm::vec3 rotation_of_second_object) {
	return false;
}

bool Boundary::Collide(Boundary* other_boundary,
                       glm::vec3 position_of_first_object,
                       glm::vec3 rotation_of_first_object,
                       glm::vec3 position_of_second_object,
                       glm::vec3 rotation_of_second_object) {
	return false;
}