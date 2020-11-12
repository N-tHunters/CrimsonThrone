#ifndef IMAGE_H
#define IMAGE_H

#include "frame.h"

class Image: public Frame {
public:
	Image(glm::vec4, std::string);
	Image(glm::vec4, GLuint);

	void draw(Shader*);
	void draw(Shader*, glm::vec3);
};

#endif