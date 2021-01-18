#ifndef MESH_H
#define MESH_H

#ifndef GLAD_MATRIX_INCLUDED
#define GLAD_MATRIX_INCLUDED

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

// Render includes

#include "shaderLoader.hpp"
#include "shaderHolder.hpp"
#include "constants.hpp"
#include "camera.hpp"

#include <string>
#include <vector>
#include <math.h>

using namespace std;

class PhysicalObj;
class Model;

/**
 * \brief Object with vertices and textures
 */

class Mesh {
	GLuint texture;
	GLuint VBO, VAO, EBO;
	PhysicalObj* obj;
	int size;
	int type;
public:
	Mesh(const string&, Model*);
	Mesh(const string&, std::vector<GLfloat>*, std::vector<unsigned int>*);
	Mesh(const string&, std::vector<GLfloat>*, std::vector<unsigned int>*, int);
	Mesh();
	void init(PhysicalObj*);
	void draw(ShaderHolder*, Camera*, GLuint, GLuint);
	void rotate(glm::vec3);
	void load(std::string);
};
#endif