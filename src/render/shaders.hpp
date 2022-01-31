#pragma once

#include <render/shaderLoader.hpp>
#include <glm/glm.hpp>

extern Shader shader3D;
extern Shader shaderGUI;
extern Shader shaderText;
extern Shader shaderWater;
extern Shader shaderPost;
extern Shader shaderText3D;
extern Shader shaderParticle;
extern glm::vec2 screen_resolution;

void load_shaders(int, int);