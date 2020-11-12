#ifndef CONTAINER_H
#define CONTAINER_H

#include "frame.h"

class Container: public Frame {
	Frame* frame;

public:
	Container(glm::vec4, Frame*, std::string);
	void draw(Shader*, Shader*, std::map<GLchar, Character>);
};

#endif