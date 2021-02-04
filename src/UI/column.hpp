#ifndef COLUMN_H
#define COLUMN_H

#include "frame.hpp"
#include "abstractListElement.hpp"
#include "text.hpp"

class Column: public Frame {
	std::vector<Frame*>* column;
	glm::vec4 rect;
	int maxCount;
	std::string header;
	int index;
	std::vector<AbstractListElement*>* list;
	std::map<GLchar, Character> characters;

public:
	Column(glm::vec4 rect, std::vector<AbstractListElement*>* list,
	       const std::string& texturePath,
	       int maxCount,
	       std::map<GLchar, Character> Characters,
	       std::string header);

	void update();

	void draw(ShaderHolder* shaderHolder) override;
};

#endif
