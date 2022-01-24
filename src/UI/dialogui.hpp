#pragma once

#include <UI/text.hpp>
#include <base/actors/actor.hpp>

class DialogUI {
	Actor* m_actor;
	std::string m_actor_line;
	std::vector<std::pair<int, std::string>> m_player_lines;

	Text* m_actor_line_text;
	std::vector<Text*> m_player_lines_text;
public:
	DialogUI(Actor* actor);
	draw(ShaderHolder*);
}