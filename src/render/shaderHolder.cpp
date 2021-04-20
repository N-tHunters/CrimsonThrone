#include "shaderHolder.hpp"

ShaderHolder::ShaderHolder(Shader* shader3D,
                           Shader* shaderGUI,
                           Shader* shaderText,
                           Shader* shaderWater,
                           Shader* shaderPost,
                           Shader* shaderText3D,
                           int screen_width,
                           int screen_height) {
	this->shader3D = shader3D;
	this->shaderGUI = shaderGUI;
	this->shaderText = shaderText;
	this->shaderWater = shaderWater;
	this->shaderPost = shaderPost;
	this->shaderText3D = shaderText3D;
	this->underWater = false;
	this->screen_width = screen_width;
	this->screen_height = screen_height;
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

Shader* ShaderHolder::getText3D() {
	return this->shaderText3D;
}

void ShaderHolder::setUnderWater(bool input) {
	this->underWater = input;
}

bool ShaderHolder::getUnderWater() {
	return this->underWater;
}

glm::vec2 ShaderHolder::getResolution() {
	return glm::vec2(this->screen_width, this->screen_height);
}