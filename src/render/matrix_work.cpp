#include <render/matrix_work.hpp>

glm::mat4 createViewMatrix(Camera* camera) {
	glm::mat4 view_matrix = glm::mat4(1.0f);

	view_matrix = glm::rotate(view_matrix, glm::radians(camera->getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
	view_matrix = glm::rotate(view_matrix, glm::radians(camera->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
	view_matrix = glm::rotate(view_matrix, glm::radians(camera->getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));

	view_matrix = glm::translate(view_matrix, -camera->getPosition());

	return view_matrix;
}