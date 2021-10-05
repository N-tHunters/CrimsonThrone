#include <render/particle.hpp>


void Particle::draw(ShaderHolder *shaderHolder) {
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  shaderHolder->getParticle()->use();

  GLint _offset = glGetUniformLocation(shaderHolder->getParticle()->Program, "offset");
  GLint _color = glGetUniformLocation(shaderHolder->getParticle()->Program, "color");

  if (life > 0.0f) {
    glUniform3fv(_offset, 1, glm::value_ptr(offset));
    glUniform4fv(_color, 1, glm::value_ptr(color));

    glBindVertexArray(particleVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
  }
  
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
