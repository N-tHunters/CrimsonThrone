#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.cpp>
#include "imageLoader.hpp"

unsigned char * loadImage(std::string path, int* width, int* height) {
	int channels;

	unsigned char * result = stbi_load(path.c_str(), width, height, &channels, STBI_rgb);

	if (result == nullptr) {
		result = stbi_load("resources/textures/error.png", width, height, &channels, STBI_rgb);		
	}

	return result;
}

void freeImage(unsigned char * image) {
	stbi_image_free(image);
}
