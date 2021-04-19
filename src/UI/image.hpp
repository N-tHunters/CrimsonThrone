#ifndef IMAGE_H
#define IMAGE_H

#include "frame.hpp"

class Image: public Frame {
	glm::vec2 m_position;
public:
	Image(glm::vec4, std::string);
	Image(glm::vec4, GLuint, glm::vec2);

	void draw(ShaderHolder*) override;
	void draw(ShaderHolder*, glm::vec3);

	void setPosition(float x, float y);
};

#endif