#include "text.hpp"

Text::Text(std::string text, glm::vec4 rect, std::map<GLchar, Character> Characters, float scale, glm::vec3 color): Frame(rect) {
	this->text = text;
	this->rect = rect;
	this->scale = scale;
	this->color = color;
	this->letters = new std::vector<Image*>;

	float x = this->rect.x;
	float y = this->rect.y;

	float width = 0.0f;
	int height = 0;

	for (size_t c = 0; c < text.size(); c ++) {
		float xpos;
		float ypos;
		float w, h;
		Character ch = Characters[text[c]];

		xpos = x + ch.Bearing.x * scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
		height = std::max(int(ch.Bearing.y / 2 * scale), height);
		width += ch.Bearing.x * scale + (ch.Advance >> 6) * scale;

		w = ch.Size.x * scale;
		h = ch.Size.y * scale;
		this->letters->push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID));
		x += (ch.Advance >> 6) * scale;
	}
	this->rect.z = width;
	this->rect.w = height;
}

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
		this->letters->push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID));
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
		this->letters->push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID));
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