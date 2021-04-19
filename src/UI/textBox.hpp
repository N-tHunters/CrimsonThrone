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
public:
	TextBox(glm::vec4 rect, std::map<GLchar, Character> Characters, float scale, glm::vec3 color, int screen_width, int screen_height);
	void draw(ShaderHolder* shaderHolder);
	void addLine(const std::string& line);
};