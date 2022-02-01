#include <render/texture.hpp>

// std::vector<GLuint> loaded_textures;
// GLuint texture;

GLuint createTexture(std::vector<unsigned char> pixels, int width, char channels) {
	int height = pixels.size() / width / channels;
	unsigned char* image = (unsigned char *)malloc(sizeof(GL_FLOAT) * pixels.size());

	for (int i = 0; i < pixels.size() / channels; i ++) {
		for (int k = 0; k < channels; k ++) {
			image[channels * i + k] = pixels[channels * i + k];
			// printf("%d\n", pixles[i * channels + k]);
		}
	}

	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLuint color_mode = GL_RGB;
	if (channels == 4) {
		color_mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);

	return texture;
}

GLuint createTexture(std::string texturePath) {
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = loadImage(texturePath, &width, &height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);

	return texture;
}