#pragma once

#include <glm/glm.hpp>
#include <render/shaderHolder.hpp>
#include <render/camera.hpp>


class Particle {
public:
  glm::vec3 pos, vel;
  glm::vec4 color;
  float life;
  float scale;

  GLuint texture;

  GLuint VAO, EBO, VBO;

  Particle(float scale, GLuint texture);
  void draw(ShaderHolder *, Camera *, int, int);
  void update(float dt);
};
