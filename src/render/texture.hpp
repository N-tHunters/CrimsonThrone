#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cstdlib>
#include <render/imageLoader.hpp>
#include <string>

void createTexture(std::vector<int>, int width, int number, GLuint* texture_ptr);
void createTexture(std::string texturePath, int number, GLuint* texture_ptr);