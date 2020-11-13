#include "list.h"


List::List(glm::vec4 rect, std::vector<AbstractListElement*>* list, std::string texturePath, int maxCount, std::map<GLchar, Character> Characters): Frame(rect) {

	this->rect = rect;
	this->maxCount = maxCount;
	this->index = 0;
}

void List::draw(ShaderHolder* shaderHolder) {
	glClear(GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shaderHolder->getGUI()->Program, "ourTexture"), 0);

	shaderHolder->getGUI()->Use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
