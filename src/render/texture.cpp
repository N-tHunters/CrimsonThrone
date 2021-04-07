#include <render/texture.hpp>

GLuint createTexture(std::vector<int> pixels, int width) {
	unsigned char* image = (unsigned char *)malloc(sizeof(GL_FLOAT) * pixels.size());

	for (int i = 0; i < pixels.size(); i ++) {
		image[i] = pixels[i];
	}

	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, pixels.size() / width / 3, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}