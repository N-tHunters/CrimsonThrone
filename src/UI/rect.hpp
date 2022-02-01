#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#ifndef GLWF_ALREADY_INCLUDED
#define GLWF_ALREADY_INCLUDED
#include <GLFW/glfw3.h>
#endif

#include <vector>
#include <render/shaders.hpp>

class Rect {
	GLuint VBO, VAO, EBO, m_texture;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;
public:
	int x, y, w, h;
	Rect(int, int, int, int);
	void draw();
	void setTexture(GLuint);
	bool checkPoint(int x, int y);
	bool checkPoint(glm::vec2 pos);
};