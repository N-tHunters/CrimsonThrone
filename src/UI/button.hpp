#ifndef BUTTON_H
#define BUTTON_H

#include <UI/frame.hpp>
#include <UI/text.hpp>

#include <render/shaders.hpp>

typedef void (*func)();

class Button: public Frame {
	glm::vec4 rect;
	func function;
	Text* text;

public:
	Button(glm::vec4 rect, func function, std::string text, std::map<GLchar, Character> Characters, float scale, glm::vec3 color);
	bool check(glm::vec2 position);
	void click(glm::vec2 position);
	void draw();
	void update(glm::vec3 color);
};

#endif