#ifndef TEXT_H
#define TEXT_H

#include "frame.hpp"
#include "image.hpp"

#include "../debug.hpp"

#include <map>

class Text: public Frame {
	std::string text;
	glm::vec3 color;
	float scale;
	glm::vec4 rect;
	std::vector<Image*>* letters;

public:
	Text(std::string, glm::vec4, std::map<GLchar, Character>, float, glm::vec3);
	void update(std::string, std::map<GLchar, Character>);
	void draw(ShaderHolder*) override;
};

#endif