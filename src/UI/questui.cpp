#include <UI/questui.hpp>

QuestUI::QuestUI(Quest* quest, ShaderHolder* shaderHolder, glm::vec2 pos, std::map<GLchar, Character> characters) {
  m_quest = quest;
  m_shaderHolder = shaderHolder;
  m_pos = pos;
  m_name_text = new Text(quest->name, characters, 1.0f, glm::vec3(1.0f), pos, 0.0f);
  m_description_text = new Text(quest->description, 0.5f, glm::vec3(1.0f), pos + glm::vec2(0, 20), 0.0f);
}

void QuestUI::draw() {
  m_name_text->draw(m_shaderHolder);
  m_description_text->draw(m_shaderHolder);
}
