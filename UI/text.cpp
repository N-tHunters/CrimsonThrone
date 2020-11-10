#include "text.h"

Text::Text(std::string text, glm::vec4 rect): Frame(rect) {
	this->text = text;
	this->rect = rect;
	this->color = glm::vec3(1.0f, 1.0f, 1.0f);
	this->scale = 160;
}

void Text::draw(Shader* shader, std::map<GLchar, Character> Characters) {
	// Activate corresponding render state
	shader->Use();
	glUniform3f(glGetUniformLocation(shader->Program, "textColor"), this->color.x, this->color.y, this->color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	
	float x = this->rect.x;

	for (c = this->text.begin(); c != this->text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * this->scale;
		GLfloat ypos = this->rect.y - (ch.Size.y - ch.Bearing.y) * this->scale;

		GLfloat w = ch.Size.x * this->scale;
		GLfloat h = ch.Size.y * this->scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos, ypos, 0.0, 1.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * this->scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

}