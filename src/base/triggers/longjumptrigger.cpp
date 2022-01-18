#include "longjumptrigger.hpp"

LongJumpTrigger::LongJumpTrigger(BoundaryBox * boundary, glm::vec3 position, glm::vec3 jump_position, Chunk * chunk) : ShortJumpTrigger(boundary, position, jump_position) {
  this->location = chunk->GetLocation();
  this->chunk = chunk;
}

LongJumpTrigger::LongJumpTrigger(PhysicalObj * link, glm::vec3 jump_position, Chunk * chunk) : ShortJumpTrigger(link, jump_position) {
  this->location = chunk->GetLocation();
  this->chunk = chunk;
}

void LongJumpTrigger::Trig(Chunk * chunk, PhysicalObj * obj) {
  ShortJumpTrigger::Trig(chunk, obj);
}

void LongJumpTrigger::TrigPlayer(Chunk * chunk, PhysicalObj * obj) {
  SetCurrentLocation(location);
  ShortJumpTrigger::Trig(chunk, obj);
}
