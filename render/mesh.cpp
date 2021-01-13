#include "mesh.h"
#include "imageLoader.h"
#include <assimp/Importer.hpp>
#include "model.h"
#include "../physics/physicalObj.h"
#include "../debug.h"

/**
 * @brief      Initializes the given object.
 *
 * @param      obj   The object
 */
void Mesh::init(PhysicalObj* obj) {
	this->obj = obj;
}

/**
 * @brief      Constructs a new instance.
 */
Mesh::Mesh() {};

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  texturePath  The texture path
 * @param      model        The model
 */
Mesh::Mesh(string texturePath, Model* model) {
	this->type = 1;
	this->obj = nullptr;
	this->size = model->indices.size();
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = loadImage(texturePath, &width, &height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Vertices

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->vertices[0]) * model->vertices.size(), &(model->vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model->indices[0]) * model->indices.size(), &(model->indices[0]), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

}

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  texturePath  The texture path
 * @param[in]  vertices     The vertices
 * @param[in]  indices      The indices
 */
Mesh::Mesh(string texturePath, std::vector<GLfloat> *vertices, std::vector<unsigned int> *indices) {
	this->type = 2;
	this->obj = nullptr;
	this->size = indices->size();
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = loadImage(texturePath, &width, &height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Vertices

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices->at(0)) * vertices->size(), &(vertices->at(0)), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices->at(0)) * indices->size(), &(indices->at(0)), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

}

/**
 * \brief Function that draw mesh
 * \param shaderHolder A holder for all the shaders
 * \param camera Player camera
 * \param width Screen width
 * \param height Screen height
 */
void Mesh::draw(ShaderHolder* shaderHolder, Camera* camera, GLuint width, GLuint height) {
	assert(this->obj != nullptr);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 cameraRot = glm::mat4(1.0f);
	glm::mat4 projection;
	glm::vec3 cameraPosition = glm::vec3(camera->getPosition().x, camera->getPosition().y + 2.f, camera->getPosition().z);
	model = glm::rotate(model, glm::radians(this->obj->getRotationX()), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(this->obj->getRotationY()), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(this->obj->getRotationZ()), glm::vec3(0.0f, 0.0f, 1.0f));
	cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
	cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
	cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::translate(view, this->obj->getPosition() - cameraPosition);
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	GLint modelLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "model");
	GLint viewLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "view");
	GLint projLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "projection");
	GLint camRotLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "cameraRot");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shaderHolder->get3D()->Program, "ourTexture"), 0);

	shaderHolder->get3D()->Use();
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(camRotLoc, 1, GL_FALSE, glm::value_ptr(cameraRot));

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
