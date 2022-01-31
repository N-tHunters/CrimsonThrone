#pragma once

#include <render/camera.hpp>
#include <render/shaders.hpp>

#ifndef GLAD_MATRIX_INCLUDED
#define GLAD_MATRIX_INCLUDED

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#endif


class Particle {
public:
  glm::vec3 pos, vel;
  glm::vec4 color;
  float life, max_life;
  float scale;

  GLuint texture;

  GLuint VAO, EBO, VBO;

  Particle(float scale, GLuint texture);
  void draw(Camera *);
  void update(float dt);
};
