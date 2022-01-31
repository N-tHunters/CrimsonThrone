#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <map>

// Render includes
#include <render/shaderLoader.hpp>
#include <render/imageLoader.hpp>


// Base includes
#include <base/items/item.hpp>

#include "character.hpp"

class Frame {

protected:
	GLuint VBO, VAO, EBO, texture;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

public:
	explicit Frame(glm::vec4);
	virtual void draw();
};

#endif
