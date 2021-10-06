#include "wanderai.hpp"
#include <random>
#include <cmath>
#include <cstdlib>
#include <math.h>
#include <math/vectors.hpp>

#define PI 3.14159265

WanderAI::WanderAI() {
  target_position = glm::vec3(rand() % 100 * 1.0f, 0.0f, rand() % 100 * 1.0f);
  target_follow_speed = rand() % 10 + 5;
}

WanderAI::WanderAI(float speed) {
  target_position = glm::vec3(rand() % 100 * 1.0f, 0.0f, rand() % 100 * 1.0f);
  target_follow_speed = speed;
  is_const_speed = true;
}

void WanderAI::Process(float dt) {
  Wander();
}

bool WanderAI::GoToTarget() {
  glm::vec3 position = this->actor->GetPhysicalObj()->getPosition(); 

  glm::vec3 rel_vec = target_position - position;
  rel_vec.y = 0;
  float degree = atan(rel_vec.x / rel_vec.z) * 180 / PI + 90;
  glm::vec3 newRotation = this->actor->GetPhysicalObj()->getRotation();
  newRotation.y = degree;
  this->actor->GetPhysicalObj()->setRotation(newRotation);
  
  rel_vec = normalize(rel_vec) * target_follow_speed;
  
  
  this->actor->GetPhysicalObj()->velocity.x = rel_vec.x;
  this->actor->GetPhysicalObj()->velocity.z = rel_vec.z;

  
  if (fabs(position.z - target_position.z) < 1.0f && fabs(position.x - target_position.x) < 1.0f)
    return true;
  return false;
}

void WanderAI::Wander() {
  if(this->GoToTarget()) {
    target_position = glm::vec3(rand() % 100 * 1.0f, 0.0f, rand() % 100 * 1.0f);
    if(!is_const_speed)
      target_follow_speed = rand() % 10 + 5;
  }
}
