#include "wanderai.hpp"
#include <random>

WanderAI::WanderAI() {
  target_position = glm::vec3(rand() % 100 * 1.0f, 0.0f, rand() % 100 * 1.0f);
  target_follow_speed = rand() % 100 + 1;
}

void WanderAI::Process() {
  Wander();
}

void WanderAI::Wander() {
  glm::vec3 position = this->actor->GetPhysicalObj()->getPosition();
  
  if (position.x < target_position.x)
    this->actor->GetPhysicalObj()->velocity.x = target_follow_speed;
  else if (position.x > target_position.x)
    this->actor->GetPhysicalObj()->velocity.x = -target_follow_speed;
  else
    this->actor->GetPhysicalObj()->velocity.x = 0;

  if (position.z < target_position.z)
    this->actor->GetPhysicalObj()->velocity.z = target_follow_speed;
  else if (position.z > target_position.z)
    this->actor->GetPhysicalObj()->velocity.z = -target_follow_speed;
  else
    this->actor->GetPhysicalObj()->velocity.z = 0;

  
  if (fabs(position.z - target_position.z) < 1.0f && fabs(position.x - target_position.x) < 1.0f) {
    target_position = glm::vec3(rand() % 100 * 1.0f, 0.0f, rand() % 100 * 1.0f);
    target_follow_speed = rand() % 100 + 1;
  }
}
