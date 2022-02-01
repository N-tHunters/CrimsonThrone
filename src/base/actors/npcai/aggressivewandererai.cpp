#include "aggressivewandererai.hpp"
#include <random>
#include <cmath>
#include <cstdlib>
#include <math.h>
#include <math/vectors.hpp>
#include <base/items/weapon.hpp>

#define PI 3.14159265

AggressiveWandererAI::AggressiveWandererAI(float speed) :
  WanderAI(speed)
{
  target = nullptr;
}

void AggressiveWandererAI::ProcessHit(Actor *enemy) {
  this->SetTarget(enemy->GetPhysicalObj());
}

void AggressiveWandererAI::Process(float dt) {
  if(target != nullptr) {
    if(GoToTarget()) {

    }
  } else {
    Wander();
  }
}

void AggressiveWandererAI::SetTarget(PhysicalObj* target) {
  this->target = target;
}

bool AggressiveWandererAI::GoToTarget() {
  glm::vec3 position = this->actor->GetPhysicalObj()->getPosition(); 

  glm::vec3 rel_vec = this->target->getPosition() - position;
  float distance = rel_vec.x * rel_vec.x + rel_vec.z * rel_vec.z;

  if((this->actor->GetWeapon() != nullptr && this->actor->GetWeapon()->GetRange() * this->actor->GetWeapon()->GetRange() >= distance + 4.0f) ||
     (this->actor->GetWeapon() == nullptr && 2.0f >= distance)) {
    return true;
  }
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
