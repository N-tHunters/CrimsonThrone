#pragma once

#include <UI/text.hpp>
#include <base/actors/actor.hpp>

class DialogUI {
	NPC* m_npc;
	std::string m_npc_line;
	std::vector<std::pair<int, std::string>> m_player_lines;

	Text* m_npc_line_text;
	std::vector<Text*> m_player_lines_text;
public:
	DialogUI(NPC* npc);
	draw(ShaderHolder*);
}