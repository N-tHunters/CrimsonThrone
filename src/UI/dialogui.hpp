#pragma once

#include <UI/text.hpp>
#include <base/actors/npc.hpp>
#include <render/shaderHolder.hpp>

class DialogUI {
	NPC* m_npc;
	std::string m_npc_line;
	std::vector<std::pair<int, std::string>> m_player_lines;

	Text* m_npc_line_text;
	std::vector<Text*> m_player_lines_text;
public:
	DialogUI(NPC* npc, std::map<GLchar, Character> characters);
	void draw(ShaderHolder*);
};