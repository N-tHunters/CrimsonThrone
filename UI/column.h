#ifndef COLUMN_H
#define COLUMN_H

#include "frame.h"
#include "abstractListElement.h"
#include "text.h"

template <class Element>
class Column: public Frame {
	std::vector<Frame*> column;
	glm::vec4 rect;
	int maxCount;
	std::string header;
	int index;

public:
	Column(glm::vec4 rect, std::vector<Element*>* list, std::string texturePath, int maxCount, std::map<GLchar, Character> Characters, std::string header): Frame(rect) {
		this->rect = rect;
		this->maxCount = maxCount;
		this->index = 0;
		this->header = header;

		for (int i = 0; i < maxCount; i ++) {
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

		// Inserting valuse one by one
		for (int i = 0; i < list->size(); i ++) {
			this->column.push_back(new Text(list->at(i)->getValues()->at(index),
		                                	glm::vec4(rect.x, rect.y + rect.w / (float)maxCount * (i + 1), rect.z, rect.w / (float)maxCount),
			                                Characters,
			                                0.001f,
			                                glm::vec3(255, 255, 0)));
		}
		this->column.push_back(new Text(header,
		                                glm::vec4(rect.x, rect.y, rect.z, rect.w / (float)maxCount),
		                                Characters,
		                                0.001f,
		                                glm::vec3(0, 255, 0)));
	}

	void draw(ShaderHolder* shaderHolder) {
		glClear(GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shaderHolder->getGUI()->Program, "ourTexture"), 0);

		shaderHolder->getGUI()->Use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		for (int i = 0; i < this->column.size(); i ++) {
			this->column[i]->draw(shaderHolder);
		}
	}

};

#endif
