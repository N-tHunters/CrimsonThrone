#ifndef TEXT_H
#define TEXT_H

#include "frame.hpp"
#include "image.hpp"

#include "../debug.hpp"

#include <map>

class Text: public Frame {
	std::string m_text;
	glm::vec3 color;
	float scale;
	std::vector<Image*>* letters;
	glm::vec2 m_position;
	glm::vec4 rect;

public:
	Text(std::string, std::map<GLchar, Character>, float, glm::vec3);
	Text(std::string, std::map<GLchar, Character>, float, glm::vec3, glm::vec2);
	Text(std::string, std::map<GLchar, Character>, float, glm::vec3, glm::vec2, float);
	void update(std::string, std::map<GLchar, Character>, glm::vec4);
	void update(std::string, std::map<GLchar, Character>);
	void draw(ShaderHolder*) override;
	glm::vec4 getRect();
	void setPosition(float x, float y);
	void changePosition(glm::vec2 delta);
	glm::vec2 getPosition();
	std::string getText();
  void setColor(glm::vec3 _color);
};

void setDefaultCharacters(std::map<GLchar, Character>);
std::map<GLchar, Character> getDefaultCharacters();


#endif
