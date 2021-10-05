#pragma once

#include <vector>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

class Joint {
public:
	int index;
	std::string name;
	std::vector<Joint*> children;
	glm::mat4 animated_transform;
	glm::mat4 local_bind_transform;
	glm::mat4 inverse_bind_transform;

	Joint(int index, std::string name, glm::mat4 local_bind_transform);

	void addChild(Joint* child);

	void calcInverseBindTransform(glm::mat4 parent_bind_transform);
};