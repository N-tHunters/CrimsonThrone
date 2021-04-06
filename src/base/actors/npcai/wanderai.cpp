#include "wanderai.hpp"
#include <random>

WanderAI::WanderAI() {
  target_position = glm::vec3(rand() % 10 * 1.0f, 0.0f, rand() % 10 * 1.0f);
}

void WanderAI::Process() {
  glm::vec3 position = this->actor->GetPhysicalObj()->getPosition();
  
  if (position.x < target_position.x)
    this->actor->GetPhysicalObj()->velocity.x = 2;
  else if (position.x > target_position.x)
    this->actor->GetPhysicalObj()->velocity.x = -2;
  else
    this->actor->GetPhysicalObj()->velocity.x = 0;

  if (position.z < target_position.z)
    this->actor->GetPhysicalObj()->velocity.z = 2;
  else if (position.z > target_position.z)
    this->actor->GetPhysicalObj()->velocity.z = -2;
  else
    this->actor->GetPhysicalObj()->velocity.z = 0;

  printf("%f %f | %f %f\n", position.x, position.z, target_position.x, target_position.z);

  
  if (fabs(position.z - target_position.z) < 1.0f && fabs(position.x - target_position.x) < 1.0f)
    target_position = glm::vec3(rand() % 10 * 1.0f, 0.0f, rand() % 10 * 1.0f);
}
