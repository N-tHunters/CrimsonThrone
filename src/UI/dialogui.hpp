#pragma once

#include <UI/text.hpp>
#include <base/actors/npc.hpp>


class DialogUI {
	NPC* m_npc;
	std::string m_npc_line;
	std::vector<std::pair<int, std::string>> m_player_lines;
	int m_width, m_height;

	Text* m_npc_line_text;
	std::vector<Text*> m_player_lines_text;
public:
	DialogUI(NPC* npc, int, int);
	void draw();
	bool click(int x, int y);
	void update();
};
