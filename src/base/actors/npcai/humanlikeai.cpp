#include "humanlikeai.hpp"

HumanlikeAI::HumanlikeAI() {
  this->hunger = 3600;
  this->hunger_threshold = 1800;
  this->gluttony_priority_modifier = 1.1;
  this->greed_modifier = 1.2;
  
  this->flags = 0;

  this->work_intensity = 2.0;
}

unsigned int HumanlikeAI::GetFlags() {
  return flags;
}

void HumanlikeAI::Process(float dt) {
  this->hunger -= (double)dt * work_intensity;
  printf("%f\n", this->hunger);

  if(this->hunger <= this->hunger_threshold) {
    printf("I want eat!\n");
  }
  
  GoToTarget();
}


void HumanlikeAI::SetActor(Actor * actor) {
  NPCAI::SetActor(actor);
  this->target_position = this->actor->GetPhysicalObj()->getPosition();
  this->target_follow_speed = 1.0f;
}
