#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <glm/glm.hpp>

class Boundary {
public:
	virtual bool Collide(Boundary*, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
};

class BoundaryBox: public Boundary {
public:
	float width, height, length;
	BoundaryBox(float, float, float);
	bool Collide(Boundary*, glm::vec3, glm::vec3, glm::vec3, glm::vec3) override;
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

#endif