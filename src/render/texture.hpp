#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cstdlib>
#include <render/imageLoader.hpp>
#include <string>

GLuint createTexture(std::vector<int>, int width);
GLuint createTexture(std::string texturePath);