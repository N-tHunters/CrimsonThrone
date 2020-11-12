#include "shaderHolder.h"

ShaderHolder::ShaderHolder(Shader* shader3D, Shader* shaderGUI, Shader* shaderText) {
	this->shader3D = shader3D;
	this->shaderGUI = shaderGUI;
	this->shaderText = shaderText;
}

Shader* ShaderHolder::get3D() {
	return this->shader3D;
}

Shader* ShaderHolder::getGUI() {
	return this->shaderGUI;
}

Shader* ShaderHolder::getText() {
	return this->shaderText;
}