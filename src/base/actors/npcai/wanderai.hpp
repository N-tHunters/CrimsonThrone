#pragma once

#include "npcai.hpp"

class WanderAI : public NPCAI {
protected:
  glm::vec3 target_position;
  float target_follow_speed;
  bool is_const_speed = false;
public:
  WanderAI();
  WanderAI(float speed);
  virtual void Process(float dt);
  virtual void Wander();
  virtual bool GoToTargetPosition();
};
