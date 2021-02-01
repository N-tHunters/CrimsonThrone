#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "imageLoader.hpp"

unsigned char * loadImage(std::string path, int* width, int* height) {
	int channels;
	
	return stbi_load(path.c_str(), width, height, &channels, STBI_rgb);
}

void freeImage(unsigned char * image) {
	stbi_image_free(image);
}