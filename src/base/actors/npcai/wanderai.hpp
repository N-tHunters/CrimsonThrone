#pragma once

#include "npcai.hpp"

class WanderAI : NPCAI {
protected:
  glm::vec3 target_position;
  float target_follow_speed;
public:
  WanderAI();
  virtual void Process();
  virtual void Wander();
  virtual bool GoToTarget();
};
