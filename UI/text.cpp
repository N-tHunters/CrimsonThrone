#include "text.h"

Text::Text(std::string text, glm::vec4 rect, std::map<GLchar, Character> Characters, float scale, glm::vec3 color): Frame(rect) {
	this->text = text;
	this->rect = rect;
	this->scale = scale;
	this->color = color;

	float x = this->rect.x;
	float y = this->rect.y;
	float xpos = 0;
	float ypos = 0;
	float w, h;

	for(int c = 0; c < text.size(); c ++) {
		Character ch = Characters[text[c]];

		xpos = x + ch.Bearing.x * scale;
		ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		w = ch.Size.x * scale;
		h = ch.Size.y * scale;
		this->letters.push_back(new Image(glm::vec4(xpos, ypos, w, h), ch.TextureID));
		x += (ch.Advance >> 6) * scale;
	}
}

void Text::draw(Shader* shader) {
	for(int i = 0; i < this->letters.size(); i ++) {
		this->letters[i]->draw(shader, this->color);
	}
}