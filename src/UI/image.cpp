#include "image.hpp"

Image::Image(glm::vec4 rect, std::string texturePath): Frame(rect) {
	vertices = {rect.x,     	 rect.y + rect.w, 0.0f, 0.0f, 1.0f,
	            rect.x,     	 rect.y,     	  0.0f, 0.0f, 0.0f,
	            rect.x + rect.z, rect.y + rect.w, 0.0f, 1.0f, 1.0f,
	            rect.x + rect.z, rect.y,     	  0.0f, 1.0f, 0.0f
	           };
	indices = {0, 1, 2,
	           1, 2, 3
	          };

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = loadImage(texturePath, &width, &height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
	glBindTexture(GL_TEXTURE_2D, 0);

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

	this->m_position = glm::vec2(0.0f, 0.0f);
}

Image::Image(glm::vec4 rect, GLuint textureID, glm::vec2 position): Frame(rect) {
	vertices = {rect.x,     	 rect.y + rect.w, 0.0f, 0.0f, 1.0f,
	            rect.x,     	 rect.y,     	  0.0f, 0.0f, 0.0f,
	            rect.x + rect.z, rect.y + rect.w, 0.0f, 1.0f, 1.0f,
	            rect.x + rect.z, rect.y,     	  0.0f, 1.0f, 0.0f
	           };
	indices = {0, 1, 2,
	           1, 2, 3
	          };

	this->texture = textureID;
	this->m_position = position;

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

void Image::draw(ShaderHolder* shaderHolder) {
	glClear(GL_DEPTH_BUFFER_BIT);

	shaderHolder->getGUI()->Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shaderHolder->getGUI()->Program, "text"), 0);
	glUniform2fv(glGetUniformLocation(shaderHolder->getGUI()->Program, "resolution"), 1, glm::value_ptr(shaderHolder->getResolution()));


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Image::draw(ShaderHolder* shaderHolder, glm::vec3 drawColor) {
	glClear(GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	shaderHolder->getText()->Use();

	glUniform1i(glGetUniformLocation(shaderHolder->getText()->Program, "text"), 0);
	glUniform3fv(glGetUniformLocation(shaderHolder->getText()->Program, "textColor"), 1, glm::value_ptr(drawColor));
	glUniform2fv(glGetUniformLocation(shaderHolder->getGUI()->Program, "resolution"), 1, glm::value_ptr(shaderHolder->getResolution()));
	glUniform2fv(glGetUniformLocation(shaderHolder->getGUI()->Program, "objectpos"), 1, glm::value_ptr(m_position));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void Image::setPosition(float x, float y) {
	this->m_position = glm::vec2(x, y);
}