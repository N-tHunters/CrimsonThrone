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

#include <render/constants.hpp>
#include <render/camera.hpp>
#include <render/texture.hpp>
#include <render/shaders.hpp>

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
	float m_scale;
public:
	bool activeDebug;
	Mesh(const std::string&, std::vector<GLfloat>*, std::vector<GLuint>*);
	Mesh(const std::string&, std::vector<GLfloat>*, std::vector<GLuint>*, int);
	Mesh(GLuint texture1,
		 GLuint texture2,
		 std::vector<GLfloat> *vertices,
		 std::vector<GLuint> *indices,
		 std::vector<unsigned char> pixels);
	Mesh(GLuint texture,
		 std::vector<GLfloat> *vertices,
		 std::vector<GLuint> *indices);
	Mesh(Model*, GLuint, float);
	Mesh(Model*, GLuint);
	Mesh();

	void loadObject(std::vector<GLfloat> *vertices, std::vector<GLuint> *indices);
	void init(PhysicalObj*);
	void draw(Camera*);
	void draw(glm::vec3 position, glm::vec3 rotation);
	void draw();
	void rotate(glm::vec3);
	void changeTexture(const std::string&);
	void loadTexture(const std::string& texturePath, char number);
};

void push_vertex(std::vector<float>* vec, glm::vec3 pos, glm::vec3 normal, glm::vec2 uv);

#endif
