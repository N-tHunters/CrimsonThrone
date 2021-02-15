#ifndef LIST_H
#define LIST_H

#include "frame.hpp"
#include "column.hpp"
#include "abstractListElement.hpp"
#include <base/items/item.hpp>

class List: public Frame {
	std::vector<Column*>* columns;
	glm::vec4 rect;
	int maxCount;
	int index;

public:
	List(glm::vec4 rect,
		std::vector<AbstractListElement*>* list,
		std::string texturePath,
		int maxCount,
		std::map<GLchar, Character> Characters,
		std::vector<std::string>* headers);

	void update();

	void draw(ShaderHolder* shaderHolder) override;
};

#endif
