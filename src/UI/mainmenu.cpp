#include <UI/mainmenu.hpp>

MainMenu::MainMenu(func play_function, func exit_function) {
	m_play_button = new Button(10, screen_resolution.y / 2 + 50 + 10, 400, 100, play_function, "Play", 0.5f, glm::vec3(1.0f), 1);
	m_exit_button = new Button(10, screen_resolution.y / 2 - 50 - 10, 400, 100, exit_function, "Exit", 0.5f, glm::vec3(1.0f), 1);
	m_rect = new Rect(0, 0, screen_resolution.x, screen_resolution.y);
	m_rect->setTexture(createTexture("resources/textures/mainmenu.jpg"));
}

void MainMenu::draw() {
	m_rect->draw();
	m_play_button->draw();
	m_exit_button->draw();
}

void MainMenu::click(int x, int y) {
	m_play_button->click(glm::vec2(x, y));
	m_exit_button->click(glm::vec2(x, y));
}

void MainMenu::highlight(int x, int y) {
	// if (m_play_button->check(glm::vec2(x, y))) {
	// 	m_play_button->update(glm::vec3(100));
	// } else {
	// 	m_play_button->update(glm::vec3(0));
	// }
}