#ifndef BAR_H
#define BAR_H

#include "frame.h"

class Bar: public Frame {
	int* value;
	int* maxValue;
	glm::vec4 rect;
public:
	Bar(glm::vec4, int*, int*, glm::vec3);
	void draw(ShaderHolder*);
};

#endif