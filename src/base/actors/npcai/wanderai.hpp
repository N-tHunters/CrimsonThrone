#pragma once

#include "npcai.hpp"

class WanderAI : NPCAI {
protected:
  glm::vec3 target_position;
public:
  WanderAI();
  virtual void Process();
};
