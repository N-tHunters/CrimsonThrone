#ifndef IMAGE_H
#define IMAGE_H

#include "frame.hpp"

class Image: public Frame {
public:
	Image(glm::vec4, std::string);
	Image(glm::vec4, GLuint);

	void draw(ShaderHolder*) override;
	void draw(ShaderHolder*, glm::vec3);
};

#endif