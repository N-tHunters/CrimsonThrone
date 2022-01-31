#pragma once

#include <UI/frame.hpp>
#include <UI/text.hpp>

class TextBox : public Frame {
	std::vector<Text*> lines;
	glm::vec4 rect;
	std::map<GLchar, Character> characters;
	char max_lines;
	glm::vec2 m_position;
	int index;
	float m_scale;
public:
	TextBox(glm::vec4 rect, std::map<GLchar, Character> Characters, float scale, glm::vec3 color);
	void draw();
	void addLine(const std::string& line);
};