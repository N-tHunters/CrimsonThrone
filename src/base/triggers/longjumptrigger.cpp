#include "longjumptrigger.hpp"

LongJumpTrigger::LongJumpTrigger(Boundary * boundary, glm::vec3 position, glm::vec3 jump_position, Chunk * chunk) : ShortJumpTrigger(boundary, position, jump_position) {
  this->location = chunk->GetLocation();
  this->chunk = chunk;
}

void LongJumpTrigger::Trig(Chunk * chunk, PhysicalObj * obj) {
  throw std::logic_error("Not implemented");
}
