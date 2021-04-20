#include "npcai.hpp"
NPCAI::NPCAI() {}

void NPCAI::SetActor(Actor * actor) {
  this->actor = actor;
}

void NPCAI::Process(float dt) {
}

void NPCAI::Communicate(Actor *) {}
