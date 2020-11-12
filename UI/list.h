#ifndef LIST_H
#define LIST_H

#include "frame.h"
#include "column.h"

class List: public Frame {
	std::vector<Column*>* columns;
	glm::vec4 rect;
	int maxCount;

public:
	List(glm::vec4, std::vector<Column*>*, std::string, int);
	void draw(Shader*);
};

#endif