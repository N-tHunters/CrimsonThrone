#pragma once

#include <base/actors/actor.hpp>

#include <render/camera.hpp>
#include <render/shaders.hpp>

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
  Text* hold_weapon;
  int weapon_index;
  
public:
  Inventory(Actor& actor);
  void draw();
  void open();
  void update(float dt);
  void nextElement();
  void prevElement();
  void selectElement();
  void updateStatus();
};
