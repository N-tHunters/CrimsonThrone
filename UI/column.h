#ifndef COLUMN_H
#define COLUMN_H

#include "frame.h"

class Column: public Frame {
	std::vector<Frame*>* column;
	glm::vec4 rect;
	int index;
	int maxCount;

public:
	List(std::vector<Frame*>*, std::string, int);
	void draw(ShaderHolder*);
};

#endif
