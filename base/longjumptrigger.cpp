#include "longjumptrigger.h"

LongJumpTrigger::LongJumpTrigger(Boundary * boundary, glm::vec3 position, glm::vec3 jump_position, Location * location, Chunk * chunk) : ShortJumpTrigger(boundary, position, jump_position) {
  this->location = location;
  this->chunk = chunk;
}

void LongJumpTrigger::Trig(PhysicalObj * obj) {
  throw std::logic_error("Not implemented");
}
