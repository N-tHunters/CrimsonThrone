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

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  texturePath  The texture path
 * @param      model        The model
 */
Mesh::Mesh(const std::string& texturePath, Model* model) {
	activeDebug = false;
	this->type = 1;
	this->obj = nullptr;
	this->size = model->indices.size();
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = loadImage(texturePath, &width, &height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width2, height2;
	unsigned char* image2 = loadImage("resources/textures/dark.png", &width2, &height2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image2);
	glBindTexture(GL_TEXTURE_2D, 1);

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

Mesh::Mesh(const std::string& texturePath, Model* model, float scale) {
	activeDebug = false;
	this->type = 1;
	this->obj = nullptr;
	this->size = model->indices.size();
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = loadImage(texturePath, &width, &height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width2, height2;
	unsigned char* image2 = loadImage("resources/textures/dark.png", &width2, &height2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image2);
	glBindTexture(GL_TEXTURE_2D, 1);

	// Vertices

	std::vector<float> vertices;

	for (int i = 0; i < model->vertices.size(); i ++) {
		if (i % 9 < 3) {
			vertices.push_back(model->vertices[i] * scale);
		} else {
			vertices.push_back(model->vertices[i]);
		}
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(model->vertices[0]) * model->vertices.size(), &(model->vertices[0]), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model->indices[0]) * model->indices.size(), &(model->indices[0]), GL_STATIC_DRAW);

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

Mesh::Mesh(Model* model, float scale, GLuint texture1) {
	activeDebug = false;
	this->type = 1;
	this->obj = nullptr;
	this->size = model->indices.size();

	this->texture1 = texture1;

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width2, height2;
	unsigned char* image2 = loadImage("resources/textures/dark.png", &width2, &height2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image2);
	glBindTexture(GL_TEXTURE_2D, 1);

	// Vertices

	std::vector<float> vertices;

	for (int i = 0; i < model->vertices.size(); i ++) {
		if (i % 8 < 3) {
			vertices.push_back(model->vertices[i] * scale);
		} else {
			vertices.push_back(model->vertices[i]);
		}
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(model->vertices[0]) * model->vertices.size(), &(model->vertices[0]), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model->indices[0]) * model->indices.size(), &(model->indices[0]), GL_STATIC_DRAW);

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

Mesh::Mesh(GLuint texture1, GLuint texture2, std::vector<GLfloat> *vertices, std::vector<unsigned int> *indices) {
	this->type = 1;
	this->obj = nullptr;
	activeDebug = false;
	this->size = indices->size();

	this->texture1 = texture1;
	this->texture2 = texture2;

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width2, height2;
	unsigned char* image2 = loadImage("resources/textures/dark.png", &width2, &height2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image2);
	glBindTexture(GL_TEXTURE_2D, 1);

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
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = loadImage(texturePath, &width, &height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int width2, height2;
	unsigned char* image2 = loadImage("resources/textures/dark.png", &width2, &height2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image2);
	glBindTexture(GL_TEXTURE_2D, 1);

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
 * \brief Function that draw mesh
 * \param[in] shaderHolder 	A holder for all the shaders
 * \param[in] camera 		Player camera
 * \param[in] width 		Screen width
 * \param[in] height 		Screen height
 */
void Mesh::draw(ShaderHolder* shaderHolder, Camera* camera, GLuint width, GLuint height) {
	assert(this->obj != nullptr);
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

	GLint modelLoc, viewLoc, projLoc, camRotLoc;

	if (this->type == 1) {
		shaderHolder->get3D()->Use();
		glUniform3fv(glGetUniformLocation(shaderHolder->get3D()->Program, "objectPos"), 1, glm::value_ptr(this->obj->getPosition()));
		glUniform3fv(glGetUniformLocation(shaderHolder->get3D()->Program, "lightPos"), 1, glm::value_ptr(lightPos));
		glUniform1f(glGetUniformLocation(shaderHolder->get3D()->Program, "underWater"), (float)(shaderHolder->getUnderWater()));
		modelLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "model");
		viewLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "view");
		projLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "projection");
		camRotLoc = glGetUniformLocation(shaderHolder->get3D()->Program, "cameraRot");
		glUniform2fv(glGetUniformLocation(shaderHolder->get3D()->Program, "resolution"), 1, glm::value_ptr(glm::vec2(width, height)));
		glUniform1i(glGetUniformLocation(shaderHolder->get3D()->Program, "Texture1"), 0);
		glUniform1i(glGetUniformLocation(shaderHolder->get3D()->Program, "Texture2"), 1);
	} else {
		shaderHolder->getWater()->Use();
		glUniform1f(glGetUniformLocation(shaderHolder->getWater()->Program, "time"), glfwGetTime());
		glUniform3fv(glGetUniformLocation(shaderHolder->getWater()->Program, "objectPos"), 1, glm::value_ptr(this->obj->getPosition()));
		glUniform3fv(glGetUniformLocation(shaderHolder->getWater()->Program, "lightPos"), 1, glm::value_ptr(lightPos));
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

void Mesh::changeTexture(const std::string& texturePath) {
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = loadImage(texturePath, &width, &height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	freeImage(image);
	glBindTexture(GL_TEXTURE_2D, 0);
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