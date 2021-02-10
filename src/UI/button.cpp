#include <UI/button.hpp>

Button::Button(glm::vec4 rect, func function, std::string text, std::map<GLchar, Character> Characters, float scale, glm::vec3 color, int screen_width, int screen_height): Frame(rect) {
	this->rect = rect;
	this->function = function;
	this->text = new Text(text, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), Characters, 1.0f / 128.0f, color);

	vertices = {rect.x,     	 rect.y + rect.w, 0.0f, 0.0f, 1.0f,
	            rect.x,     	 rect.y,     	  0.0f, 0.0f, 0.0f,
	            rect.x + rect.z, rect.y + rect.w, 0.0f, 1.0f, 1.0f,
	            rect.x + rect.z, rect.y,     	  0.0f, 1.0f, 0.0f
	           };
	indices = {0, 1, 2,
	           1, 2, 3
	          };

	rect.x = (rect.x + 1.0f) / 2.0f * screen_width;
	rect.y = (rect.y + 1.0f) / 2.0f * screen_height;
	rect.z = rect.z / 2.0f * screen_width;
	rect.w = rect.w / 2.0f * screen_height;

	glm::vec2 center = glm::vec2(rect.x + rect.z / 2.0f, rect.y + rect.w / 2.0f);

	glm::vec2 textPosition = glm::vec2(center.x - this->text->getRect().z / 2.0f, center.y - this->text->getRect().w / 2.0f);

	this->text->update(text, Characters, glm::vec4(textPosition / glm::vec2(screen_width, screen_height) * 2.0f - 1.0f,
	                   glm::vec2(this->text->getRect().z, this->text->getRect().w) / glm::vec2(screen_width, screen_height) * 2.0f - 1.0f));

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

	width = (int)(rect.z);
	height = (int)(rect.w);

	printf("%d %d\n", width, height);

	unsigned char* image = (unsigned char *)malloc(width * height * 3 * sizeof(GL_FLOAT));
	// image[0] = 0.0f;
	// image[1] = 255.0f;
	// image[2] = 0.0f;

	for (int i = 0; i < (int)(rect.w); i ++) {
		for (int j = 0; j < (int)(rect.z); j ++) {
			if (i <= 3 || j <= 3 || i >= height - 4 || j >= width - 4) {
				image[(int)(i * rect.z + j) * 3] = 255.0f;
				image[(int)(i * rect.z + j) * 3 + 1] = 255.0f;
				image[(int)(i * rect.z + j) * 3 + 2] = 255.0f;
			} else {
				image[(int)(i * rect.z + j) * 3] = 0.0f;
				image[(int)(i * rect.z + j) * 3 + 1] = 0.0f;
				image[(int)(i * rect.z + j) * 3 + 2] = 0.0f;
			}
		}
	}
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

void Button::draw(ShaderHolder* shaderHolder) {
	glClear(GL_DEPTH_BUFFER_BIT);

	shaderHolder->getGUI()->Use();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shaderHolder->getGUI()->Program, "ourTexture"), 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	this->text->draw(shaderHolder);
}