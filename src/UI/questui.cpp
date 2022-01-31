#include <UI/questui.hpp>

QuestUI::QuestUI(Quest* quest, glm::vec2 pos, std::map<GLchar, Character> characters) {
  m_quest = quest;
  m_pos = pos;
  m_name_text = new Text(quest->name, characters, 0.3f, glm::vec3(1.0f), pos, 0.0f);
  m_description_text = new Text(quest->description, characters, 0.2f, glm::vec3(1.0f), pos - glm::vec2(0, 20), 0.0f);
  m_goals_text.clear();
  for (int i = 0; i < quest->goals.size(); i ++) {
    m_goals_text.push_back(new Text(quest->goals[i]->description, characters, 0.2f, glm::vec3(1.0f), pos - glm::vec2(0, 20 * (i + 2)), 0.0f));
  }
}

void QuestUI::draw() {
  m_name_text->draw();
  m_description_text->draw();
  for (int i = 0; i < m_goals_text.size(); i ++) {
    m_goals_text[i]->draw();
  }
}
