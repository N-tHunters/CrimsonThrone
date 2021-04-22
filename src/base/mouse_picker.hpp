#pragma once

// INCLUDES

// Inner includes
#include <render/camera.hpp>
#include <render/matrix_work.hpp>

// Side includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class MousePicker
{
	glm::vec3 m_current_ray;
	glm::mat4 m_projection_matrix;
	glm::mat4 m_view_matrix;

	Camera* m_camera;

public:
	MousePicker(Camera* camera, glm::mat4 projection_matrix);

	glm::vec3 getCurrentRay();

	void update();

	glm::vec3 calculateMouseRay();
	glm::vec3 toWorldSpace(glm::vec4 eye_coords);
	glm::vec4 toEyeCoords(glm::vec4 clip_coords);
	
};