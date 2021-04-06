#include "npcai.hpp"
NPCAI::NPCAI() {}

void NPCAI::SetActor(Actor * actor) {
  this->actor = actor;
}

void NPCAI::Process() {
}
void NPCAI::Communicate(Actor *) {}
