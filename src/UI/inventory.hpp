#pragma once

#include <base/actors/actor.hpp>
#include <render/shaderHolder.hpp>
#include <render/camera.hpp>

class Inventory {
  Actor& actor;
  int index = 0;
  glm::vec4 rect;
  glm::vec4 color;
  GLuint VBO, VAO, EBO, texture;
  std::vector<GLfloat> vertices;
  std::vector<unsigned int> indices;

public:
  Inventory(Actor& actor, int, int);
  void draw(ShaderHolder* shaderHolder, int width, int height);
  void update();
};
