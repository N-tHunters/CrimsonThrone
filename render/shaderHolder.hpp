#ifndef SHADERS_H
#define SHADERS_H

#include "shaderLoader.hpp"

class ShaderHolder {
  Shader* shader3D;
  Shader * shaderGUI;
  Shader * shaderText;
  Shader * shaderWater;

public:
	ShaderHolder(Shader*, Shader*, Shader*, Shader*);
	Shader* get3D();
	Shader* getGUI();
	Shader* getText();
	Shader* getWater();
};

#endif