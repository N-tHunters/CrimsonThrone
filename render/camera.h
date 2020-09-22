#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
	glm::vec3 position;
	glm::vec3 rotation;
public:
	Camera(glm::vec3, glm::vec3);
	glm::vec3 getPosition();
	glm::vec3 getRotation();
	void setPosition(glm::vec3);
	void setRotation(glm::vec3);
	void setRotationX(float);
	void setRotationY(float);
	void setRotationZ(float);
	void changePosition(glm::vec3);
	void changePositionX(float);
	void changePositionY(float);
	void changePositionZ(float);
	void changeRotation(glm::vec3);
	void changeRotationX(float);
	void changeRotationY(float);
	void changeRotationZ(float);
};
#endif