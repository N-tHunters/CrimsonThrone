#include <render/texture.hpp>

// std::vector<GLuint> loaded_textures;
// GLuint texture;

void createTexture(std::vector<int> pixels, int width, int number, GLuint* texture_ptr) {
	int height = pixels.size() / width / 3;
	unsigned char* image = (unsigned char *)malloc(sizeof(GL_FLOAT) * pixels.size());

	for (int i = 0; i < pixels.size() / 3; i ++) {
		image[4 * i] = pixels[3 * i];
		image[4 * i + 1] = pixels[3 * i + 1];
		image[4 * i + 2] = pixels[3 * i + 2];
		image[4 * i + 3] = 255;
	}

	// GLuint texture;

	// loaded_textures.push_back(texture);

	glGenTextures(1, texture_ptr);
	glBindTexture(GL_TEXTURE_2D, *texture_ptr); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps

	// glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
	// glBindTexture(GL_TEXTURE_2D, texture);
}

void createTexture(std::string texturePath, int number, GLuint* texture_ptr) {
	// GLuint texture;

	// loaded_textures.push_back(texture);

	glGenTextures(1, texture_ptr);
	glBindTexture(GL_TEXTURE_2D, *texture_ptr); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = loadImage(texturePath, &width, &height);
	// glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
	// glBindTexture(GL_TEXTURE_2D, texture);
}