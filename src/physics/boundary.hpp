#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class BoundaryBox{
	glm::vec3 m_min;
	glm::vec3 m_max;
public:
	BoundaryBox(glm::vec3 min, glm::vec3 max);
	bool Collide(BoundaryBox*, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
	glm::vec3 getMin();
	glm::vec3 getMax();
};

float CollideRayWithBox(glm::vec3 ray_position, glm::vec3 ray_direction, BoundaryBox* box, glm::vec3 box_position, glm::vec3 box_rotation);