#pragma once

#include <base/actors/actor.hpp>
#include <render/shaderHolder.hpp>
#include <render/camera.hpp>

class Inventory {
  Actor& actor;
  int index = 0;

public:
  Inventory(Actor& actor);
  void draw(ShaderHolder* shaderHolder);
  void update();
};
