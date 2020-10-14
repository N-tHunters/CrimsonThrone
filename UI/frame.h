#ifndef FRAME_H
#define FRAME_H

#include "../render/shaderLoader.h"
#include <vector>
#include <string>
#include "../render/imageLoader.h"

class Frame {

protected:
	Frame* frame;
	GLuint VBO, VAO, EBO, texture;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

public:
	Frame(float, float, float, float, std::string);
	Frame(Frame*, float, float, float, float);
	void draw(Shader*);
};

class Image: public Frame {
public:
	Image(float, float, float, float, std::string);
};

#endif