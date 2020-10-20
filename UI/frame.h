#ifndef FRAME_H
#define FRAME_H

#include "../render/shaderLoader.h"
#include <vector>
#include <string>
#include "../render/imageLoader.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

class Frame {

protected:
	GLuint VBO, VAO, EBO, texture;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

public:
	Frame(glm::vec4);
	void draw(Shader*);
};

class Container: public Frame {
	Frame* frame;
public:
	Container(glm::vec4, Frame*, std::string);
	void draw(Shader*);
};

class Image: public Frame {
public:
	Image(glm::vec4, std::string);
};

class Bar: public Frame {
	int* value;
	int* maxValue;
	glm::vec4 rect;
public:
	Bar(glm::vec4, int*, int*, glm::vec3);
	void draw(Shader*);
};

template <class T>
class List: public Frame {
	std::vector<T*> list;
	glm::vec4 rect;
	int maxCount;
	int index;

public:
	List(glm::vec4, std::vector<T*>, std::string, int);
	void draw(Shader*);
};

#endif