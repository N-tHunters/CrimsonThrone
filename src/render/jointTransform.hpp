#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <render/quaternion.hpp>

class JointTransform {
	glm::vec3 position;
	Quaternion* rotation;

	JointTransform(glm::vec3 position, Quaternion* rotation) {
		this->position = position;
		this->rotation = rotation;
	}

	glm::mat4 get_local_transform() {
		glm::mat4 matrix;
		matrix = glm::translate(matrix, position);
		matrix = matrix * rotation->to_matrix();

		return matrix;
	}

	JointTransform* interpolate()
};