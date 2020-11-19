#ifndef LIST_H
#define LIST_H

#include "frame.h"
#include "column.h"
#include "abstractListElement.h"

class List: public Frame {
	std::vector<Column*> columns;
	glm::vec4 rect;
	int maxCount;
  int index;

public:
	List(glm::vec4, std::vector<AbstractListElement*>*, std::string, int, std::map<GLchar, Character>);
	void draw(ShaderHolder*);
};

#endif
