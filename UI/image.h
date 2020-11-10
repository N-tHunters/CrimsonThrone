#ifndef IMAGE_H
#define IMAGE_H

#include "frame.h"

class Image: public Frame {
public:
	Image(glm::vec4, std::string);
};

#endif