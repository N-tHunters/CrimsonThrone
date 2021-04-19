#include "text.hpp"

Text::Text(std::string text,
		   std::map<GLchar, Character> Characters,
		   float scale,
		   glm::vec3 color,
		   glm::vec2 position
		): Frame(glm::vec4(0.0f)) {
	this->text = text;
	this->rect = rect;
	this->scale = scale;
	this->color = color;
	this->letters = new std::vector<Image*>;
	m_position = position;

	float width = 0.0f;
	int height = 0;

	for (size_t c = 0; c < text.size(); c ++) {
		Character ch = Characters[text[c]];

		width += ch.Bearing.x * scale + (ch.Advance >> 6) * scale;
		height = std::max(int(ch.Bearing.y / 2 * scale), height);
	}

	float x = - width / 2.0f;
	float y = - height / 2.0f;

	for (size_t c = 0; c < text.size(); c ++) {
		float xpos;
		float ypos;
		float w, h;
		Character ch = Characters[text[c]];

		xpos = x + ch.Bearing.x * scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		w = ch.Size.x * scale;
		h = ch.Size.y * scale;
		this->letters->push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID, m_position));
		x += (ch.Advance >> 6) * scale;
	}
	this->rect.z = width;
	this->rect.w = height;
}

Text::Text(std::string text,
		   std::map<GLchar, Character> Characters,
		   float scale,
		   glm::vec3 color) : Text(text, Characters, scale, color, glm::vec2(0.0f)) {}

void Text::update(std::string text, std::map<GLchar, Character> Characters, glm::vec4 rect) {
	this->text = text;
	this->rect = rect;

	float x = this->rect.x;
	float y = this->rect.y;

	this->letters->clear();

	float width, height;
	width = 0.0f;
	height = 0.0f;

	for (size_t c = 0; c < text.size(); c ++) {
		float xpos;
		float ypos;
		float w, h;
		Character ch = Characters[text[c]];

		xpos = x + ch.Bearing.x * this->scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * this->scale;

		width += ch.Bearing.x * this->scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * this->scale;

		w = ch.Size.x * scale;
		h = ch.Size.y * scale;
		this->letters->push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID, m_position));
		x += (ch.Advance >> 6) * scale;
	}

	this->rect.z = width;
	this->rect.w = height;
}

void Text::update(std::string text, std::map<GLchar, Character> Characters) {
	this->text = text;

	float x = this->rect.x;
	float y = this->rect.y;

	this->letters->clear();

	for (size_t c = 0; c < text.size(); c ++) {
		float xpos;
		float ypos;
		float w, h;
		Character ch = Characters[text[c]];

		xpos = x + ch.Bearing.x * this->scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * this->scale;

		w = ch.Size.x * scale;
		h = ch.Size.y * scale;
		this->letters->push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID, m_position));
		x += (ch.Advance >> 6) * scale;
	}
}

void Text::draw(ShaderHolder* shaderHolder) {
	for (size_t i = 0; i < this->letters->size(); i ++)
		this->letters->at(i)->draw(shaderHolder, this->color);
}

glm::vec4 Text::getRect() {
	return this->rect;
}

void Text::setPosition(float x, float y) {
	for (int i = 0; i < this->letters->size(); i ++) {
		this->letters->at(i)->setPosition(x, y);
	}

	m_position = glm::vec2(x, y);
}

void Text::changePosition(glm::vec2 delta) {
	this->m_position += delta;

	for (int i = 0; i < this->letters->size(); i ++) {
		this->letters->at(i)->setPosition(m_position.x, m_position.y);
	}
}

glm::vec2 Text::getPosition() {
	return m_position;
}