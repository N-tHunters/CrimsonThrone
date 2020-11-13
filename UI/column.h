#ifndef COLUMN_H
#define COLUMN_H

#include "frame.h"
#include "abstractListElement.h"
#include "text.h"

class Column: public Frame {
	std::vector<Frame*> column;
	//glm::vec4 rect;
	int maxCount;
	std::string header;

public:
	Column(std::vector<AbstractListElement*>*, std::string, std::string, int, std::map<GLchar, Character>);
	void draw(ShaderHolder*);
};

#endif
