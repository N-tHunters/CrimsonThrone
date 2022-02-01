#pragma once

#include <UI/button.hpp>
#include <UI/rect.hpp>
#include <render/texture.hpp>

typedef void (*func)();

class MainMenu {
	Button* m_play_button;
	Button* m_exit_button;
	Rect* m_rect;
public:
	MainMenu(func, func);
	void draw();
	void click(int, int);
	void highlight(int, int);
};