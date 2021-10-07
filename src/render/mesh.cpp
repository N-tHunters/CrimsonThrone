#include "mesh.hpp"
#include "imageLoader.hpp"
#include <assimp/Importer.hpp>
#include "model.hpp"
#include "../physics/physicalObj.hpp"
#include "../debug.hpp"

/**
 * @brief      Initializes the given object.
 *
 * @param      obj   The object
 */
void Mesh::init(PhysicalObj* obj) {
	this->obj = obj;
	activeDebug = false;
}

/**
 * @brief      Constructs a new instance.
 */
Mesh::Mesh() {};

Mesh::Mesh(Model* model, GLuint texture) : Mesh(model, texture, 1.0f) {}

Mesh::Mesh(Model* model, GLuint texture1, float scale) {
	activeDebug = false;
	this->type = 1;
	this->obj = nullptr;
	this->size = model->indices.size();
	m_scale = scale;

	this->texture1 = texture1;
	this->loadTexture("resources/textures/dark.png", 1);
	this->loadTexture("resources/textures/blend.png", 2);

	loadObject(&(model->vertices), &(model->indices));
}

Mesh::Mesh(GLuint texture1, GLuint texture2, std::vector<GLfloat> *vertices, std::vector<unsigned int> *indices, std::vector<unsigned char> pixels) {
	this->type = 1;
	this->obj = nullptr;
	activeDebug = false;
	this->size = indices->size();

	m_scale = 1.0f;

	this->texture1 = texture1;
	this->texture2 = texture2;
	// this->blend_texture = blend_texture;

	int width = 32;
	int height = 32;

	unsigned char* image = (unsigned char *)malloc(sizeof(GL_FLOAT) * pixels.size());

	/*for (int i = 0; i < pixels.size(); i ++) {
		image[i] = pixels[i];
	}*/

	for (int i = 0; i < width; i ++) {
		for (int j = 0; j < height; j ++) {
			image[(i * width + j) * 4] = pixels[(i + j * width) * 4];
			image[(i * width + j) * 4 + 1] = pixels[(i + j * width) * 4 + 1];
			image[(i * width + j) * 4 + 2] = pixels[(i + j * width) * 4 + 2];
			image[(i * width + j) * 4 + 3] = pixels[(i + j * width) * 4 + 3];
		}
	}

	glGenTextures(1, &blend_texture);
	glBindTexture(GL_TEXTURE_2D, blend_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
	
	loadObject(vertices, indices);
}


/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  texturePath  The texture path
 * @param[in]  vertices     The vertices
 * @param[in]  indices      The indices
 */
Mesh::Mesh(const std::string& texturePath, std::vector<GLfloat> *vertices, std::vector<unsigned int> *indices) : Mesh(texturePath, vertices, indices, 1) {}

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  texturePath  The texture path
 * @param[in]  vertices     The vertices
 * @param[in]  indices      The indices
 * @param[in]  type			The type
 */
Mesh::Mesh(const std::string& texturePath, std::vector<GLfloat> *vertices, std::vector<unsigned int> *indices, int type) {
	this->type = type;
	this->obj = nullptr;
	activeDebug = false;
	this->size = indices->size();

	m_scale = 1.0f;

	// createTexture(texturePath);
	// createTexture("resources/textures/dark.png");
	// createTexture("resources/textures/blend.png");

	this->loadTexture(texturePath, 0);
	this->loadTexture("resources/textures/dark.png", 1);
	this->loadTexture("resources/textures/blend.png", 2);

	loadObject(vertices, indices);
}

void Mesh::loadObject(std::vector<GLfloat> *vertices, std::vector<unsigned int> *indices) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices->at(0)) * vertices->size(), &(vertices->at(0)), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices->at(0)) * indices->size(), &(indices->at(0)), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

/**
 * \brief Function that draws mesh
 * \param[in] shaderHolder 	A holder for all the shaders
 * \param[in] camera 		Player camera
 * \param[in] width 		Screen width
 * \param[in] height 		Screen height
 */
void Mesh::draw(ShaderHolder* shaderHolder, Camera* camera, GLuint width, GLuint height) {
	// assert(this->obj != nullptr);
	if (this->obj == nullptr) {
		draw(shaderHolder, glm::vec3(0.0f), glm::vec3(0.0f), width, height);
		return;
	}
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 cameraRot = glm::mat4(1.0f);
	glm::mat4 projection;
	glm::vec3 cameraPosition = glm::vec3(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
	model = glm::rotate(model, glm::radians(this->obj->getRotationX()), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(this->obj->getRotationY()), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(this->obj->getRotationZ()), glm::vec3(0.0f, 0.0f, 1.0f));
	cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
	cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
	cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::translate(view, this->obj->getPosition() - cameraPosition);
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

	glm::vec3 lightPos = glm::vec3(20, 1, 20);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glActiveTexture(GL_TEXTURE2);
	
	// printf("First: %04x\n", glGetError());
	glBindTexture(GL_TEXTURE_2D, blend_texture);
	// printf("%04x\n", blend_texture);
	// printf("Second: %04x\n", glGetError());


	GLint modelLoc, viewLoc, projLoc, camRotLoc;

	if (this->type == 1) {
		shaderHolder->get3D()->Use();
		glUniform3fv(glGetUniformLocation(shaderHolder->get3D()->Program, "objectPos"), 1, glm::value_ptr(this->obj->getPosition()));
		glUniform3fv(glGetUniformLocation(shaderHolder->get3D()->Program, "lightPos"), 1, glm::value_ptr(lightPos));
		glUniform1f(glGetUniformLocation(shaderHolder->get3D()->Program, "underWater"), (float)(shaderHolder->getUnderWater()));
		glUniform1f(glGetUniformLocation(shaderHolder->get3D()->Program, "scale"), m_scale);
		modelLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "model");
		viewLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "view");
		projLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "projection");
		camRotLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "cameraRot");
		glUniform2fv(glGetUniformLocation(shaderHolder->get3D()->Program, "resolution"), 1, glm::value_ptr(glm::vec2(width, height)));
		glUniform1i(glGetUniformLocation(shaderHolder->get3D()->Program, "Texture1"), 0);
		glUniform1i(glGetUniformLocation(shaderHolder->get3D()->Program, "Texture2"), 1);
		glUniform1i(glGetUniformLocation(shaderHolder->get3D()->Program, "blend_texture"), 2);
	} else {
		shaderHolder->getWater()->Use();
		glUniform1f(glGetUniformLocation(shaderHolder->getWater()->Program, "time"), glfwGetTime());
		glUniform3fv(glGetUniformLocation(shaderHolder->getWater()->Program, "objectPos"), 1, glm::value_ptr(this->obj->getPosition()));
		glUniform3fv(glGetUniformLocation(shaderHolder->getWater()->Program, "lightPos"), 1, glm::value_ptr(lightPos));
		glUniform1f(glGetUniformLocation(shaderHolder->getWater()->Program, "scale"), m_scale);
		modelLoc = glGetUniformLocation(shaderHolder->getWater()->Program, "model");
		viewLoc = glGetUniformLocation(shaderHolder->getWater()->Program, "view");
		projLoc = glGetUniformLocation(shaderHolder->getWater()->Program, "projection");
		camRotLoc = glGetUniformLocation(shaderHolder->getWater()->Program, "cameraRot");
		glUniform1i(glGetUniformLocation(shaderHolder->getWater()->Program, "Texture1"), 0);
		// glUniform1i(glGetUniformLocation(shaderHolder->getWater()->Program, "Texture2"), 1);
	}

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(camRotLoc, 1, GL_FALSE, glm::value_ptr(cameraRot));

	// print_vector(this->obj->getPosition());

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::draw(ShaderHolder* shaderHolder, glm::vec3 position, glm::vec3 rotation, GLuint width, GLuint height) {
	assert(this->obj != nullptr);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 cameraRot = glm::mat4(1.0f);
	glm::mat4 projection;
	// glm::vec3 cameraPosition = glm::vec3(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	//cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
	//cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
	//cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::translate(view, position);
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

	glm::vec3 lightPos = glm::vec3(20, 1, 20);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glActiveTexture(GL_TEXTURE2);
	
	// printf("First: %04x\n", glGetError());
	glBindTexture(GL_TEXTURE_2D, blend_texture);
	// printf("%04x\n", blend_texture);
	// printf("Second: %04x\n", glGetError());


	GLint modelLoc, viewLoc, projLoc, camRotLoc;

	shaderHolder->get3D()->Use();
	glUniform3fv(glGetUniformLocation(shaderHolder->get3D()->Program, "objectPos"), 1, glm::value_ptr(this->obj->getPosition()));
	glUniform3fv(glGetUniformLocation(shaderHolder->get3D()->Program, "lightPos"), 1, glm::value_ptr(lightPos));
	glUniform1f(glGetUniformLocation(shaderHolder->get3D()->Program, "underWater"), (float)(shaderHolder->getUnderWater()));
	glUniform1f(glGetUniformLocation(shaderHolder->get3D()->Program, "scale"), m_scale);
	modelLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "model");
	viewLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "view");
	projLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "projection");
	camRotLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "cameraRot");
	glUniform2fv(glGetUniformLocation(shaderHolder->get3D()->Program, "resolution"), 1, glm::value_ptr(glm::vec2(width, height)));
	glUniform1i(glGetUniformLocation(shaderHolder->get3D()->Program, "Texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderHolder->get3D()->Program, "Texture2"), 1);
	glUniform1i(glGetUniformLocation(shaderHolder->get3D()->Program, "blend_texture"), 2);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(camRotLoc, 1, GL_FALSE, glm::value_ptr(cameraRot));

	// print_vector(this->obj->getPosition());

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::changeTexture(const std::string& texturePath) {
	// this->texture1 = createTexture(texturePath, 0);
}

void Mesh::loadTexture(const std::string& texturePath, char number) {
	if (number == 0) {
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);
	} else if (number == 1) {
		glGenTextures(1, &texture2);
		glBindTexture(GL_TEXTURE_2D, texture2);
	} else {
		glGenTextures(1, &blend_texture);
		glBindTexture(GL_TEXTURE_2D, blend_texture);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = loadImage(texturePath, &width, &height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
}


void Mesh::draw(ShaderHolder* shaderHolder) {
  printf("not implemented\n");
}


void push_vertex(std::vector<float>* vec, glm::vec3 pos, glm::vec3 normal, glm::vec2 uv) {
	vec->push_back(pos.x);
	vec->push_back(pos.y);
	vec->push_back(pos.z);

	vec->push_back(normal.x);
	vec->push_back(normal.y);
	vec->push_back(normal.z);

	vec->push_back(uv.x);
	vec->push_back(uv.y);
}
