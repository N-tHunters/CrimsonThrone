#pragma once

#include <glm/glm.hpp>
#include <render/shaderHolder.hpp>
#include <render/camera.hpp>


class Particle {
public:
  glm::vec3 pos, vel;
  glm::vec4 color;
  float life;

  Particle():
    pos(0.0f), vel(0.0f), color(1.0f), life(0.0f) {}
  void draw(ShaderHolder *, Camera *, int, int);
};
