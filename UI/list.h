#ifndef LIST_H
#define LIST_H

#include "frame.h"

template <class T>
class List: public Frame {
	std::vector<T>* list;
	glm::vec4 rect;
	int maxCount;
	int index;

public:
	List(glm::vec4, std::vector<T>*, std::string, int);
	void draw(Shader*);
};

#endif