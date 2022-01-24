#include <UI/dialogui.hpp>

DialogUI::DialogUI(Actor* actor, std::map<GLchar, Character> characters) {
	m_actor = actor;
	m_actor_line = actor->getLine();
	m_player_lines = actor->getPlayerLines();

	m_actor_line_text = new Text(m_actor_line, characters, 1.0f, glm::vec3(1), glm::vec2(0.0f, 0.5f));
}

void DialogUI::draw(ShaderHolder* shaderHolder) {
	m_actor_line_text->draw(shaderHolder);
}