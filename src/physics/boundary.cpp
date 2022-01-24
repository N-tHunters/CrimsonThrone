#include "boundary.hpp"
#include <iostream>
#include <glm/glm.hpp>

BoundaryBox::BoundaryBox(glm::vec3 min, glm::vec3 max) {
	m_min = min;
	m_max = max;
};

glm::vec3 BoundaryBox::getMin() {
	return m_min;
}

glm::vec3 BoundaryBox::getMax() {
	return m_max;
}

bool BoundaryBox::Collide(BoundaryBox* other_boundary,
						  glm::vec3 position,
						  glm::vec3 rotation,
						  glm::vec3 other_position,
						  glm::vec3 other_rotation) {
	glm::vec3 my_p0 = position + m_min;
	glm::vec3 my_p1 = position + m_max;
	glm::vec3 other_p0 = other_position + other_boundary->getMin();
	glm::vec3 other_p1 = other_position + other_boundary->getMax();

	bool x = my_p1.x >= other_p0.x && other_p1.x >= my_p0.x;
	bool y = my_p1.y >= other_p0.y && other_p1.y >= my_p0.y;
	bool z = my_p1.z >= other_p0.z && other_p1.z >= my_p0.z;

	return x && y && z;
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

	glm::vec3 p0 = box_position + box->getMin();
	glm::vec3 p1 = box_position + box->getMax();

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

	tmin = std::max(std::max(tmin, tymin), tzmin);

	if (tmin < 0.0f) {
		return 0.0f;
	}

	return tmin;
}

/*

boxpos.x + box.width >= x * direction.x >= boxpos.x - box.width
boxpos.y + box.height >= x * direction.y >= boxpos.y - box.height
boxpos.z + box.length >= x * direction.z >= boxpos.z - box.length

(boxpos.x + box.width) / direction.x

*/