#pragma once

#include <UI/button.hpp>

typedef void (*func)();

class MainMenu {
	Button* m_play_button;
	Button* m_exit_button;
public:
	MainMenu(func, func);
	void draw();
	void click(int, int);
	void highlight(int, int);
};