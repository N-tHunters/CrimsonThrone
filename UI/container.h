#ifndef CONTAINER_H
#define CONTAINER_H

#include "frame.h"

/**
 * @brief      This class describes a container for frames, useless.
 */
class Container: public Frame {
	Frame* frame;

public:
	Container(glm::vec4, Frame*, std::string);
	void draw(ShaderHolder*) override;
};

#endif