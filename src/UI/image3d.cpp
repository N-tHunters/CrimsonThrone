#include <UI/image3d.hpp>

Image3D::Image3D(glm::vec4 rect, glm::vec3 position, GLuint texture) {
	m_rect = rect;
	m_position = position;
	m_texture = texture;

	vertices = {
		rect.x,     	 rect.y + rect.w, 0.0f, 0.0f, 1.0f,
		rect.x,     	 rect.y,     	  0.0f, 0.0f, 0.0f,
		rect.x + rect.z, rect.y + rect.w, 0.0f, 1.0f, 1.0f,
		rect.x + rect.z, rect.y,     	  0.0f, 1.0f, 0.0f
	};

	indices = {
		0, 1, 2,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &(indices[0]), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	m_size = indices.size();
}

void Image3D::draw(Shader* shader, Camera* camera, GLuint width, GLuint height) {
	glClear(GL_DEPTH_BUFFER_BIT);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 cameraRot = glm::mat4(1.0f);
	glm::mat4 projection;
	glm::vec3 cameraPosition = glm::vec3(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
	// model = glm::rotate(model, glm::radians(-camera->getRotation().z), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-camera->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
	// model = glm::rotate(model, glm::radians(-camera->getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
	cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
	cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
	cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::translate(view, m_position - cameraPosition);
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

	glm::vec3 lightPos = glm::vec3(20, 1, 20);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	// glActiveTexture(GL_TEXTURE2);
	// glBindTexture(GL_TEXTURE_2D, blend_texture);

	GLint modelLoc, viewLoc, projLoc, camRotLoc;

	shader->Use();
	modelLoc = glGetUniformLocation(shader->Program, "model");
	viewLoc = glGetUniformLocation(shader->Program, "view");
	projLoc = glGetUniformLocation(shader->Program, "projection");
	camRotLoc = glGetUniformLocation(shader->Program, "cameraRot");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(camRotLoc, 1, GL_FALSE, glm::value_ptr(cameraRot));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Image3D::setPosition(glm::vec3 position) {
	m_position = position;
}
