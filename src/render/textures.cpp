#include <render/textures.hpp>

std::unordered_map<std::string, GLuint> textures;

void load_textures(std::vector<std::string> texture_names) {
	for (int i = 0; i < texture_names.size(); i ++) {
		glGenTextures(1, &(textures[texture_names[i]]));
		glBindTexture(GL_TEXTURE_2D, textures[texture_names[i]]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		int width, height;

		unsigned char* image = loadImage("resources/textures/" + texture_names[i] + ".png", &width, &height);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		freeImage(image);
	}
}

GLuint get_texture(std::string texture_name) {
	if (textures.find(texture_name) == textures.end()) {
		printf("ERROR::TEXTURE::NOT_FOUND: Texture \"%s\" not found\n", texture_name.c_str());
	}
	return textures[texture_name];
}