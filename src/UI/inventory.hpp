#pragma once

#include <base/actors/actor.hpp>
#include <render/shaderHolder.hpp>
#include <render/camera.hpp>
#include <UI/text.hpp>

class Inventory {
  Actor& actor;
  int index = 0;
  glm::vec4 rect;
  glm::vec4 color;
  glm::vec3 element_rotation;
  GLuint VBO, VAO, EBO, texture;
  std::vector<GLfloat> vertices;
  std::vector<unsigned int> indices;
  std::vector<Text*>item_names;
  std::map<GLchar, Character> &characters;

public:
  Inventory(Actor& actor, std::map<GLchar, Character> &Characters, int, int);
  void draw(ShaderHolder* shaderHolder, int width, int height);
  void update();
};
