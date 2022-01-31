#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <render/camera.hpp>
#include <render/shaders.hpp>


class Image3D {
	glm::vec4 m_rect;
	glm::vec3 m_position;
	GLuint m_texture;
	GLuint VAO, VBO, EBO;
	unsigned int m_size;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

public:
	Image3D(glm::vec4 rect, glm::vec3 position, GLuint texture);
	void draw(Camera* camera);
	void setPosition(glm::vec3 position);
};
