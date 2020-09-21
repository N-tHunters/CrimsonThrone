#ifndef MESH_H
#define MESH_H // holds all OpenGL type declarations

#ifndef GLAD_MATRIX_INCLUDED
#define GLAD_MATRIX_INCLUDED

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

#include "shaderLoader.h"

#include <string>
#include <vector>

#include <SOIL.h>
#include "constants.h"

using namespace std;

class Mesh {
	GLuint texture;
	GLuint VBO, VAO, EBO;
	glm::vec3 rotation;
	glm::vec3 position;
	int size;
public:
	Mesh(string texturePath, std::vector<GLfloat> vertices, std::vector<GLuint> indices, glm::vec3 rotation, glm::vec3 position);

	void draw(Shader shader, glm::vec3 cameraRotation, glm::vec3 cameraPosition);

	void rotate(glm::vec3 deltaRotation);

	void load(std::string filename);
};
#endif