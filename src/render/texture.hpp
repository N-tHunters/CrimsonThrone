#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cstdlib>
#include <render/imageLoader.hpp>
#include <string>

GLuint createTexture(std::vector<unsigned char>, int width, char channels);
GLuint createTexture(std::string texturePath);