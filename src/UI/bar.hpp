#ifndef BAR_H
#define BAR_H

#include <UI/frame.hpp>

class Bar: public Frame {
	int* value;
	int* maxValue;
	glm::vec4 rect;
public:
	Bar(glm::vec4, int*, int*, glm::vec3);
	void draw(ShaderHolder*, int, int);
};

#endif