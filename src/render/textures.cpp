#include <render/textures.hpp>

std::unordered_map<std::string, GLuint> textures;

void load_textures(std::vector<std::string> texture_names) {
	for (int i = 0; i < texture_names.size(); i ++) {
		glGenTextures(1, &(textures[texture_names[i]]));
		glBindTexture(GL_TEXTURE_2D, textures[texture_names[i]]); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
		// Set our texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// Load, create texture and generate mipmaps
		int width, height;

		// auto t1 = std::chrono::high_resolution_clock::now();

		unsigned char* image = loadImage("resources/textures/" + texture_names[i] + ".png", &width, &height);

		// auto t2 = std::chrono::high_resolution_clock::now();
		// printf("%f\n", std::chrono::duration<double, std::milli>(t2 - t1).count());

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		freeImage(image);
	}
}

GLuint get_texture(std::string texture_name) {
	return textures[texture_name];
}

/*
glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;

	// auto t1 = std::chrono::high_resolution_clock::now();

	unsigned char* image = loadImage(texturePath, &width, &height);

	// auto t2 = std::chrono::high_resolution_clock::now();
	// printf("%f\n", std::chrono::duration<double, std::milli>(t2 - t1).count());

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
	glBindTexture(GL_TEXTURE_2D, 0);
*/