#ifndef BUTTON_H
#define BUTTON_H

#include <UI/frame.hpp>
#include <UI/text.hpp>
#include <UI/rect.hpp>

#include <render/shaders.hpp>
#include <render/texture.hpp>

typedef void (*func)();

class Button {
	Rect* rect;
	func function;
	Text* text;

public:
	Button(glm::vec2 size, glm::vec2 pos, func function, std::string text, float scale, glm::vec3 color);
	Button(int, int, int, int, func, std::string, float, glm::vec3);
	bool check(glm::vec2 position);
	void click(glm::vec2 position);
	void draw();
	void update(glm::vec3 color);
};

#endif
