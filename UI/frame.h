#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <map>

// Render includes
#include "../render/shaderLoader.h"
#include "../render/imageLoader.h"
#include "../render/shaderHolder.h"

// Base includes
#include "../base/item.h"

#include "character.h"

class Frame {

protected:
	GLuint VBO, VAO, EBO, texture;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

public:
	Frame(glm::vec4);
	virtual void draw(ShaderHolder*);
};

#endif