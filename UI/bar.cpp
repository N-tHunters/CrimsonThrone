#include "bar.hpp"

Bar::Bar(glm::vec4 rect, int* value, int* maxValue, glm::vec3 color) : Frame(rect) {
	this->value = value;
	this->maxValue = maxValue;
	this->rect = rect;

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = (unsigned char *)malloc(3);
	image[0] = color.x;
	image[1] = color.y;
	image[2] = color.z;
	width = 1;
	height = 1;
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
}

void Bar::draw(ShaderHolder* shaderHolder) {
	glClear(GL_DEPTH_BUFFER_BIT);

	this->vertices[10] = this->rect.x + this->rect.z * (*this->value / *this->maxValue);
	this->vertices[15] = this->rect.x + this->rect.z * (*this->value / *this->maxValue);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shaderHolder->getGUI()->Program, "ourTexture"), 0);

	shaderHolder->getGUI()->Use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}