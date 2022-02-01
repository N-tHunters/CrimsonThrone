#include <UI/rect.hpp>

Rect::Rect(int x, int y, int w, int h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	vertices = {0, h, 0, 0, 1,
	            0, 0, 0, 0, 0,
	            w, h, 0, 1, 1,
	            w, 0, 0, 1, 0
	           };
	indices = {0, 1, 2,
	           1, 2, 3
	          };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &(indices[0]), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Rect::draw() {
	shaderGUI.Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glUniform1i(glGetUniformLocation(shaderGUI.Program, "ourTexture"), 0);
	glUniform2fv(glGetUniformLocation(shaderGUI.Program, "objectpos"), 1, glm::value_ptr(glm::vec2(x, y)));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Rect::setTexture(GLuint texture) {
	m_texture = texture;
}

void Rect::setPosition(int new_x, int new_y) {
	x = new_x;
	y = new_y;
}

bool Rect::checkPoint(int px, int py) {
	bool x_col = px >= x && px <= x + w;
	bool y_col = py >= y && py <= y + h;
	return x_col && y_col;
}

bool Rect::checkPoint(glm::vec2 pos) {
	return checkPoint((int)(pos.x), (int)(pos.y));
}