#include "column.hpp"

Column::Column(glm::vec4 rect, std::vector<AbstractListElement*>* list, const std::string& texturePath, int maxCount, std::map<GLchar, Character> Characters, std::string header): Frame(rect) {
	this->rect = rect;
	this->maxCount = maxCount;
	this->index = 0;
	this->header = header;
	this->column = new std::vector<Frame*>;
	this->list = list;
	this->characters = Characters;

	for (size_t i = 0; i < maxCount; i ++) {
		this->vertices.push_back(rect.x);
		this->vertices.push_back(rect.y + rect.w / maxCount * (i + 1));
		this->vertices.push_back(0.0f);
		this->vertices.push_back(0.0f);
		this->vertices.push_back(1.0f);

		this->vertices.push_back(rect.x);
		this->vertices.push_back(rect.y + rect.w / maxCount * i);
		this->vertices.push_back(0.0f);
		this->vertices.push_back(0.0f);
		this->vertices.push_back(0.0f);

		this->vertices.push_back(rect.x + rect.z);
		this->vertices.push_back(rect.y + rect.w / maxCount * (i + 1));
		this->vertices.push_back(0.0f);
		this->vertices.push_back(1.0f);
		this->vertices.push_back(1.0f);

		this->vertices.push_back(rect.x + rect.z);
		this->vertices.push_back(rect.y + rect.w / maxCount * i);
		this->vertices.push_back(0.0f);
		this->vertices.push_back(1.0f);
		this->vertices.push_back(0.0f);
		this->indices.push_back(0 + i * 4);
		this->indices.push_back(1 + i * 4);
		this->indices.push_back(2 + i * 4);
		this->indices.push_back(1 + i * 4);
		this->indices.push_back(2 + i * 4);
		this->indices.push_back(3 + i * 4);
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

	// Creating header for this column

	float tile_width = rect.w / (float)maxCount;
	float letter_height = Characters['a'].Size.y;

	glm::vec4 header_rect = glm::vec4(rect.x + 0.01, rect.y + rect.w - tile_width / 2 - letter_height / 2 * 0.001f, rect.z, rect.w / (float)maxCount);

	this->column->push_back(new Text(header,
	                                 header_rect,
	                                 Characters,
	                                 0.001f,
	                                 glm::vec3(0)));

	// Inserting valuse one by one
	for (uint16_t i = 0; i < list->size(); i ++) {
		this->column->push_back(new Text(list->at(i)->getValues()->at(index),
		                                 glm::vec4(rect.x, rect.y + rect.w / (float)maxCount * (i + 1), rect.z, rect.w / (float)maxCount),
		                                 Characters,
		                                 0.001f,
		                                 glm::vec3(1.0, 1.0, 0)));
	}
}

void Column::update() {
	float tile_width = this->rect.w / (float)(this->maxCount);
	float letter_height = characters['a'].Size.y;

	glm::vec4 header_rect = glm::vec4(this->rect.x + 0.01, this->rect.y + this->rect.w - tile_width / 2 - letter_height / 2 * 0.001f, this->rect.z, tile_width);

	this->column->clear();

	this->column->push_back(new Text(this->header,
	                                 header_rect,
	                                 characters,
	                                 0.001f,
	                                 glm::vec3(0)));

	// Inserting valuse one by one
	for (uint16_t i = 0; i < this->list->size(); i ++) {
		this->column->push_back(new Text(this->list->at(i)->getValues()->at(this->index),
		                                 glm::vec4(this->rect.x, this->rect.y + tile_width * (i + 1), this->rect.z, tile_width),
		                                 characters,
		                                 0.001f,
		                                 glm::vec3(1.0, 1.0, 0)));
	}
}

void Column::draw(ShaderHolder* shaderHolder) {
	glClear(GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shaderHolder->getGUI()->Program, "ourTexture"), 0);

	shaderHolder->getGUI()->Use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	for (size_t i = 0; i < this->column->size(); i ++) {
		this->column->at(i)->draw(shaderHolder);
	}
}