#include <glm/glm.hpp>

class Camera {
	glm::vec3 position;
	glm::vec3 rotation;
public:
	glm::vec3 getPosition();
	glm::vec3 getRotation();
	void setPosition(glm::vec3);
	void setRotation(glm::vec3);
	void changePosition(glm::vec3);
	void changeRotation(glm::vec3);
};