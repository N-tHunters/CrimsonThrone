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

float CollideRayWithBox(glm::vec3 ray_position, glm::vec3 ray_direction, BoundaryBox* box, glm::vec3 box_position, glm::vec3 box_rotation) {
	box_position -= ray_position;
	glm::mat4 rotation_matrix = glm::mat4(1.0f);
	rotation_matrix = glm::rotate(rotation_matrix, glm::radians(-box_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotation_matrix = glm::rotate(rotation_matrix, glm::radians(-box_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotation_matrix = glm::rotate(rotation_matrix, glm::radians(-box_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 temp_vec = rotation_matrix * glm::vec4(ray_direction, 1.0f);
	ray_direction = glm::vec3(temp_vec.x, temp_vec.y, temp_vec.z);

	temp_vec = rotation_matrix * glm::vec4(box_position, 1.0f);
	box_position = glm::vec3(temp_vec.x, temp_vec.y, temp_vec.z);

	glm::vec3 p0 = box_position - glm::vec3(box->width, box->height, box->length);
	glm::vec3 p1 = box_position + glm::vec3(box->width, box->height, box->length);

	glm::vec3 bounds[2] = {p0, p1};

	char sign_x = 0;
	if (ray_direction.x < 0) {
		sign_x = 1;
	}

	float tmin = bounds[sign_x].x / ray_direction.x;
	float tmax = bounds[1 - sign_x].x / ray_direction.x;

	char sign_y = 0;
	if (ray_direction.y < 0) {
		sign_y = 1;
	}

	float tymin = bounds[sign_y].y / ray_direction.y;
	float tymax = bounds[1 - sign_y].y / ray_direction.y;

	if ((tmin > tymax) || (tymin > tmax)) {
		return 0.0;
	}
	if (tymin > tmin) {
		tmin = tymin;
	}
	if (tymax < tmax) {
		tmax = tymax;
	}

	char sign_z = 0;
	if (ray_direction.z < 0.0f) {
		sign_z = 1;
	}

	float tzmin = bounds[sign_z].z / ray_direction.z;
	float tzmax = bounds[1 - sign_z].z / ray_direction.z;

	if ((tmin > tzmax) || (tzmin > tmax)) {
		return 0.0f;
	}
	if (tzmin > tmin) {
		tmin = tzmin;
	}
	if (tzmax < tmax) {
		tmax = tzmax;
	}

	return std::max(std::max(tmin, tymin), tzmin);
}

/*

boxpos.x + box.width >= x * direction.x >= boxpos.x - box.width
boxpos.y + box.height >= x * direction.y >= boxpos.y - box.height
boxpos.z + box.length >= x * direction.z >= boxpos.z - box.length

(boxpos.x + box.width) / direction.x

*/