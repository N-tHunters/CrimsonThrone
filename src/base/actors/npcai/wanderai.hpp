#pragma once

#include "npcai.hpp"

class WanderAI : public NPCAI {
protected:
  glm::vec3 target_position;
  float target_follow_speed;
public:
  WanderAI();
  virtual void Process(float dt);
  virtual void Wander();
  virtual bool GoToTarget();
};
