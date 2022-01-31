#pragma once

#include <UI/frame.hpp>

#include <render/shaders.hpp>

class Bar: public Frame {
	int* value;
	int* maxValue;
	glm::vec4 rect;
public:
	Bar(glm::vec4, int*, int*, glm::vec3);
	void draw(int, int);
};