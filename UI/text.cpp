#include "text.h"

Text::Text(std::string text, glm::vec4 rect, std::map<GLchar, Character> Characters, float scale, glm::vec3 color): Frame(rect) {
	this->text = text;
	this->rect = rect;
	this->scale = scale;
	this->color = color;

	float x = this->rect.x;
	float y = this->rect.y;

	for (int c = 0; c < text.size(); c ++) {
		float xpos;
		float ypos;
		float w, h;
		Character ch = Characters[text[c]];

		xpos = x + ch.Bearing.x * scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		w = ch.Size.x * scale;
		h = ch.Size.y * scale;
		this->letters.push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID));
		x += (ch.Advance >> 6) * scale;
	}
}

void Text::update(std::string text, std::map<GLchar, Character> Characters) {
	this->text = text;

	float x = this->rect.x;
	float y = this->rect.y;

	this->letters.clear();

	for (int c = 0; c < text.size(); c ++) {
		float xpos;
		float ypos;
		float w, h;
		Character ch = Characters[text[c]];

		xpos = x + ch.Bearing.x * this->scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * this->scale;

		w = ch.Size.x * scale;
		h = ch.Size.y * scale;
		this->letters.push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID));
		x += (ch.Advance >> 6) * scale;
	}
}

void Text::draw(ShaderHolder* shaderHolder) {
	for (int i = 0; i < this->letters.size(); i ++) {
		//printf("Letters: %f %f %f\n", this->color.x, this->color.y, this->color.z);
		this->letters[i]->draw(shaderHolder, this->color);
	}
}
