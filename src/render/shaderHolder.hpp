#ifndef SHADERS_H
#define SHADERS_H

#include <render/shaderLoader.hpp>
#include <glm/glm.hpp>

class ShaderHolder {
	Shader * shader3D;
	Shader * shaderGUI;
	Shader * shaderText;
	Shader * shaderWater;
	Shader * shaderPost;
	Shader * shaderText3D;
	bool underWater;
	int screen_width;
	int screen_height;

public:
	ShaderHolder(Shader*, Shader*, Shader*, Shader*, Shader*, Shader*, int, int);
	Shader* get3D();
	Shader* getGUI();
	Shader* getText();
	Shader* getWater();
	Shader* getPost();
	Shader* getText3D();

	void setUnderWater(bool input);
	bool getUnderWater();
	glm::vec2 getResolution();
};

#endif
