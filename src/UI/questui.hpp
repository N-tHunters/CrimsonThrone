#pragma once

#include <base/quests/quest.hpp>
#include <glm/glm.hpp>
#include <UI/text.hpp>

class QuestUI {
  Quest* m_quest;
  ShaderHolder* m_shaderHolder;
  Text* m_name_text;
  Text* m_description_text;
  std::vector<Text*> m_goals_text;
  glm::vec2 m_pos;
public:
  QuestUI(Quest* quest, ShaderHolder* shaderHolder, glm::vec2 pos, std::map<GLchar, Character> characters);
  void draw();
};
