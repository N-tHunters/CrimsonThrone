#include "humanlikeai.hpp"

HumanlikeAI::HumanlikeAI() {
  this->hunger = 1000000;
  this->hunger_threshold = 100000;
  this->gluttony_priority_modifier = 1.1;
  this->greed_modifier = 1.2;
  
  this->flags = 0;
}

unsigned int HumanlikeAI::GetFlags() {
  return flags;
}
