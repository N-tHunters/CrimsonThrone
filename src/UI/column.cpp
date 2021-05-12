#include "column.hpp"

Column::Column(glm::vec4 rect, std::vector<AbstractListElement*>* list, const std::string& texturePath, int maxCount, std::map<GLchar, Character> Characters, std::string header, int width, int height, int index): Frame(rect) {
	this->rect = rect;
	this->maxCount = maxCount;
	this->index = index;
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
	unsigned char* image = (unsigned char *)malloc(3 * width * height * sizeof(GL_FLOAT));

	for (int i = 0; i < height; i ++) {
		for (int j = 0; j < width; j ++) {
			float r, g, b;
			if (i < 3 || j < 3 || i > height - 4 || j > width - 4) {
				r = 255.0f;
				g = 255.0f;
				b = 255.0f;
			} else {
				r = 0.0f;
				g = 0.0f;
				b = 0.0f;
			}
			image[(i * width + j) * 3] = r;
			image[(i * width + j) * 3 + 1] = g;
			image[(i * width + j) * 3 + 2] = b;
		}
	}

	//unsigned char* image = loadImage(texturePath, &width, &height);
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

	// glm::vec4 header_rect = glm::vec4(rect.x + 0.01, rect.y + rect.w - tile_width / 2 - letter_height / 2 * 0.001f, rect.z, rect.w / (float)maxCount);


	/*this->column->push_back(new Text(header,
	                                 Characters,
	                                 0.001f,
	                                 glm::vec3(0)));*/

	// Inserting valuse one by one
	for (uint16_t i = 0; i < list->size(); i ++) {
		this->column->push_back(new Text(list->at(i)->getValues()->at(index),
		                                 // glm::vec4(rect.x, rect.y + rect.w / (float)maxCount * (i + 1), rect.z, rect.w / (float)maxCount),
		                                 Characters,
		                                 1.0f,
		                                 glm::vec3(1.0, 1.0, 0)));
	}

	header_text = new Text(header,
		Characters,
		24.0f / 24.0f,
		glm::vec3(255),
		glm::vec2(rect.x + rect.z / 2.0f,
			rect.y + tile_width * maxCount - tile_width / 2.0f));
}

void Column::update() {
	float tile_width = this->rect.w / (float)(this->maxCount);
	float letter_height = characters['a'].Size.y;

	// glm::vec4 header_rect = glm::vec4(this->rect.x + 0.01, this->rect.y + this->rect.w - tile_width / 2 - letter_height / 2 * 0.001f, this->rect.z, tile_width);

	this->column->clear();

	/*this->column->push_back(new Text(this->header,
	                                 characters,
	                                 0.001f,
	                                 glm::vec3(0)));*/

	// Inserting valuse one by one

	for (uint16_t i = 0; i < this->list->size(); i ++) {
		this->column->push_back(new Text(this->list->at(i)->getValues()->at(this->index).c_str(),
		                                 // glm::vec4(this->rect.x, this->rect.y + tile_width * (i + 1), this->rect.z, tile_width),
		                                 characters,
		                                 1.0f,
		                                 glm::vec3(255.0, 255.0, 0),
		                                 glm::vec2(rect.x + rect.z / 2.0f,
			rect.y + tile_width * maxCount - tile_width / 2.0f - tile_width * (i + 1))));
	}
}

void Column::draw(ShaderHolder* shaderHolder) {
	glClear(GL_DEPTH_BUFFER_BIT);
	
	shaderHolder->getGUI()->Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shaderHolder->getGUI()->Program, "ourTexture"), 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	header_text->draw(shaderHolder);

	for (size_t i = 0; i < this->column->size(); i ++) {
		this->column->at(i)->draw(shaderHolder);
		// printf("Column %s, row %d, value: %s\n", this->header.c_str(), i, ((Text*)(this->column->at(i)))->getText().c_str());
	}
}
