#ifndef LIST_H
#define LIST_H

#include "frame.hpp"
#include "column.hpp"
#include "abstractListElement.hpp"
#include "../base/item.h"

template <class Element>
class List: public Frame {
	std::vector<Column<Element>*> columns;
	glm::vec4 rect;
	int maxCount;
	int index;

public:
	List(glm::vec4 rect, std::vector<Element*>* list, std::string texturePath, int maxCount, std::map<GLchar, Character> Characters, std::vector<std::string>* headers): Frame(rect) {
		this->rect = rect;
		this->maxCount = maxCount;
		this->index = 0;

		for (size_t i = 0; i < headers->size(); i ++) {
			this->columns.push_back(new Column<Element>(glm::vec4(rect.x + rect.z / (float)headers->size() * i,
			                        rect.y, rect.z / (float)headers->size(), rect.w), list, texturePath, 10, Characters, headers->at(i)));
		}

	}
	void draw(ShaderHolder* shaderHolder) override {

		for (int i = 0; i < this->columns.size(); i ++) {
			this->columns.at(i)->draw(shaderHolder);
		}

	}
};

#endif
