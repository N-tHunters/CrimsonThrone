#ifndef TEXT_H
#define TEXT_H

#include "frame.h"

#include <map>

class Text: public Frame {
	std::string text;
	glm::vec3 color;
	float scale;
	glm::vec4 rect;

public:
	Text(std::string, glm::vec4);
	void draw(Shader*, std::map<GLchar, Character>);
};

#endif