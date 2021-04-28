#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Boundary {
public:
	virtual bool Collide(Boundary*, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
};

class BoundaryBox: public Boundary {
	glm::vec3 m_min;
	glm::vec3 m_max;
public:
	BoundaryBox(glm::vec3 min, glm::vec3 max);
	bool Collide(BoundaryBox*, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
	glm::vec3 getMin();
	glm::vec3 getMax();
};

class BoundaryCapsule: public Boundary {
public:
	float height, radius;
	BoundaryCapsule(float, float);
	bool Collide(Boundary*, glm::vec3, glm::vec3, glm::vec3, glm::vec3) override;
};

class BoundaryPlane: public Boundary {
public:
	float width, height;
	BoundaryPlane(float, float);
	bool Collide(Boundary*, glm::vec3, glm::vec3, glm::vec3, glm::vec3) override;
};

class BoundarySphere: public Boundary {
public:
	float radius;
	explicit BoundarySphere(float);
	bool Collide(Boundary*, glm::vec3, glm::vec3, glm::vec3, glm::vec3) override;
};

float CollideRayWithBox(glm::vec3 ray_position, glm::vec3 ray_direction, BoundaryBox* box, glm::vec3 box_position, glm::vec3 box_rotation);