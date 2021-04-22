#include <base/mouse_picker.hpp>

MousePicker::MousePicker(Camera* camera, glm::mat4 projection_matrix) {
	m_camera = camera;
	m_projection_matrix = projection_matrix;
	m_view_matrix = createViewMatrix(camera);
}

glm::vec3 MousePicker::getCurrentRay() {
	return m_current_ray;
}

void MousePicker::update() {
	m_view_matrix = createViewMatrix(m_camera);
	m_current_ray = calculateMouseRay();
}

glm::vec3 MousePicker::calculateMouseRay() {
	glm::vec4 clip_coords = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
	glm::vec4 eye_coords = toEyeCoords(clip_coords);
	glm::vec3 world_ray = toWorldSpace(eye_coords);

	return world_ray;
}

glm::vec3 MousePicker::toWorldSpace(glm::vec4 eye_coords) {
	glm::mat4 inverse_view = glm::inverse(m_view_matrix);
	glm::vec4 ray_world = inverse_view * eye_coords;
	glm::vec3 mouse_ray = glm::vec3(ray_world.x, ray_world.y, ray_world.z);
	mouse_ray = glm::normalize(mouse_ray);

	return mouse_ray;
}

glm::vec4 MousePicker::toEyeCoords(glm::vec4 clip_coords) {
	glm::mat4 inverse_projection = glm::inverse(m_projection_matrix);
	glm::vec4 eye_coords = inverse_projection * clip_coords;

	return glm::vec4(eye_coords.x, eye_coords.y, -1.0f, 0.0f);
}