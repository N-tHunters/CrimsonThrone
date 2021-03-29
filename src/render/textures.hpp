#pragma once

#include <GL/glew.h>
#include <render/imageLoader.hpp>

#include <unordered_map>
#include <vector>
#include <string>

void load_textures(std::vector<std::string> texture_names);
GLuint get_texture(std::string texture_name);