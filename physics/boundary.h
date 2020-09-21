class Boundary {
public:
	virtual bool Collide(Boundary*, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
};

class BoundaryBox: public Boundary {
public:
	float width, height, length;
	BoundaryBox(float, float, float);
	bool Collide(Boundary*, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
};

class BoundaryCapsule: public Boundary {
public:
	float height, radius;
	BoundaryCapsule(float, float);
	bool Collide(Boundary*, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
};

class BoundaryPlane: public Boundary {
public:
	float width, length;
	BoundaryPlane(float, float);
	bool Collide(Boundary*, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
};

class BoundarySphere: public Boundary {
public:
	float radius;
	BoundaryPlane(float);
	bool Collide(Boundary*, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
};