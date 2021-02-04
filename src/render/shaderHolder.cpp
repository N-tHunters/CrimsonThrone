#include "shaderHolder.hpp"

ShaderHolder::ShaderHolder(Shader* shader3D, Shader* shaderGUI, Shader* shaderText, Shader* shaderWater, Shader* shaderPost) {
	this->shader3D = shader3D;
	this->shaderGUI = shaderGUI;
	this->shaderText = shaderText;
	this->shaderWater = shaderWater;
	this->shaderPost = shaderPost;
	this->underWater = false;
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

Shader* ShaderHolder::getWater() {
	return this->shaderWater;
}

Shader* ShaderHolder::getPost() {
	return this->shaderPost;
}

void ShaderHolder::setUnderWater(bool input) {
	this->underWater = input;
}

bool ShaderHolder::getUnderWater() {
	return this->underWater;
}