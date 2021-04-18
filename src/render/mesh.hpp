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
#include <render/shaderLoader.hpp>
#include <render/shaderHolder.hpp>
#include <render/constants.hpp>
#include <render/camera.hpp>
#include <render/texture.hpp>

#include <string>
#include <vector>
#include <math.h>
#include <chrono>

class PhysicalObj;
class Model;

/**
 * @brief Object that renders
 * @author Altrul
 */
class Mesh {
protected:
	GLuint texture1; /**< The first texture of the object */
	GLuint texture2; /**< The second texture of the object */
	GLuint blend_texture; /**< The texture used to blend textures in needed way */
	GLuint VBO; /**< Vertex Buffer Object */
	GLuint VAO; /**< Vertex Array Object */
	GLuint EBO; /**< Element Buffer Object */
	PhysicalObj* obj; /**< PhysicalObj that this mesh is bond to */
	int size; /**< The number of indices this mesh has */
	int type; /**< The type. 0 = water, 1 = object. Later will be removed */
public:
	bool activeDebug;
	Mesh(const std::string&, std::vector<GLfloat>*, std::vector<unsigned int>*);
	Mesh(const std::string&, std::vector<GLfloat>*, std::vector<unsigned int>*, int);
	Mesh(GLuint texture1,
		 GLuint texture2,
		 std::vector<GLfloat> *vertices,
		 std::vector<unsigned int> *indices,
		 std::vector<unsigned char> pixels);
	Mesh(Model*, GLuint, float);
	Mesh(Model*, GLuint);
	Mesh();

	void loadObject(std::vector<GLfloat> *vertices, std::vector<unsigned int> *indices);
	void init(PhysicalObj*);
	void draw(ShaderHolder*, Camera*, GLuint, GLuint);
	void rotate(glm::vec3);
	void changeTexture(const std::string&);
};

void push_vertex(std::vector<float>* vec, glm::vec3 pos, glm::vec3 normal, glm::vec2 uv);

#endif