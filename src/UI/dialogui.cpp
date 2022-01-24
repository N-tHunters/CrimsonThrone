#include <UI/dialogui.hpp>

DialogUI::DialogUI(NPC* npc, std::map<GLchar, Character> characters) {
	m_npc = npc;
	m_npc_line = npc->getDialog()->getLine();
	m_player_lines = npc->getDialog()->getPlayerLines();

	m_npc_line_text = new Text(m_npc_line, characters, 1.0f, glm::vec3(1), glm::vec2(0.0f, 0.5f));
}

void DialogUI::draw(ShaderHolder* shaderHolder) {
	m_npc_line_text->draw(shaderHolder);
}