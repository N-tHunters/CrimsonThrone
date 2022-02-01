#include <UI/dialogui.hpp>

DialogUI::DialogUI(NPC* npc, int width, int height) {
	m_npc = npc;
	m_width = width;
	m_height = height;

	update();
}

void DialogUI::draw() {
	m_npc_line_text->draw();

	for (Text* player_line_text: m_player_lines_text) {
		player_line_text->draw();
	}
}

void DialogUI::update() {
	m_player_lines_text.clear();
	m_npc_line = m_npc->getDialog()->getLine();
	m_player_lines = m_npc->getDialog()->getPlayerLines();

	m_npc_line_text = new Text(m_npc_line, 0.2f, glm::vec3(1), glm::vec2(m_width * 0.5, m_height * 0.25));

	for (int i = 0; i < m_player_lines.size(); i ++) {
		Text* player_line_text = new Text(m_player_lines[i].second, 0.2f, glm::vec3(1), glm::vec2(20, m_height * 0.75 - i * 50), 0.0f);
		m_player_lines_text.push_back(player_line_text);
	}
}

bool DialogUI::click(int x, int y) {
	for (int i = 0; i < m_player_lines_text.size(); i ++) {
		glm::vec4 rect = m_player_lines_text[i]->getRect();
		if (x > rect.x && y > rect.y && x < rect.x + rect.z and y < rect.y + rect.w) {
			if (m_player_lines[i].first == -1) {
				return true;
			}
			m_npc->getDialog()->nextLine(m_player_lines[i].first);
			update();
			return false;
		}
	}

	return false;
}
