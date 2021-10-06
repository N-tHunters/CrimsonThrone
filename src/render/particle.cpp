#include <render/particle.hpp>
#include <glm/gtc/type_ptr.hpp>

Particle::Particle(float scale, GLuint texture) : pos(0.0f), vel(0.0f), color(1.0f), life(0.0f), scale(scale) {
  float vertices[16] = {
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f, 1.0f
  };

  int indices[6] = {
    0, 1, 2,
    0, 2, 3
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, indices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  // TexCoord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0); // Unbind VAO

  this->texture = texture;
}

void Particle::draw(ShaderHolder *shaderHolder, Camera * camera, int width, int height) {
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 cameraRot = glm::mat4(1.0f);
  glm::mat4 projection;
  glm::vec3 cameraPosition = glm::vec3(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
  cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
  cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
  cameraRot = glm::rotate(cameraRot, glm::radians(camera->getRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
  view = glm::translate(view, pos - cameraPosition);
  projection = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, texture);

  shaderHolder->getParticle()->Use();

  GLuint _offset = glGetUniformLocation(shaderHolder->getParticle()->Program, "offset");
  GLuint _color = glGetUniformLocation(shaderHolder->getParticle()->Program, "color");
  GLuint _projection = glGetUniformLocation(shaderHolder->getParticle()->Program, "projection");
  GLuint _cameraRot = glGetUniformLocation(shaderHolder->getParticle()->Program, "cameraRot");
  GLuint _view = glGetUniformLocation(shaderHolder->getParticle()->Program, "view");
  GLuint _scale = glGetUniformLocation(shaderHolder->getParticle()->Program, "scale");

  if (life > 0.0f) {
    glUniform3fv(_offset, 1, glm::value_ptr(glm::vec3(0.0f)));
    glUniform4fv(_color, 1, glm::value_ptr(color));
    glUniform1f(_scale, scale);
    glUniformMatrix4fv(_projection, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(_cameraRot, 1, GL_FALSE, glm::value_ptr(cameraRot));
    glUniformMatrix4fv(_view, 1, GL_FALSE, glm::value_ptr(view));

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
  
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Particle::update(float dt) {
  this->pos += this->vel * dt;
  this->life -= dt;
}
