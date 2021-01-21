#ifndef SHADERS_H
#define SHADERS_H

#include "shaderLoader.hpp"

class ShaderHolder {
  Shader* shader3D;
  Shader * shaderGUI;
  Shader * shaderText;
  Shader * shaderWater;
  bool underWater;

public:
	ShaderHolder(Shader*, Shader*, Shader*, Shader*);
	Shader* get3D();
	Shader* getGUI();
	Shader* getText();
	Shader* getWater();

	void setUnderWater(bool input);
	bool getUnderWater();
};

#endif
