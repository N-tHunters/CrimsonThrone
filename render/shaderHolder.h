#ifndef SHADERS_H
#define SHADERS_H

#include "shaderLoader.h"

class ShaderHolder {
  Shader* shader3D;
  Shader * shaderGUI;
  Shader * shaderText;

public:
	ShaderHolder(Shader*, Shader*, Shader*);
	Shader* get3D();
	Shader* getGUI();
	Shader* getText();
};

#endif
