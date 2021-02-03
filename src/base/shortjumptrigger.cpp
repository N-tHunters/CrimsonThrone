#include "shortjumptrigger.hpp"

ShortJumpTrigger::ShortJumpTrigger(Boundary * boundary, glm::vec3 position, glm::vec3 jump_position) : BoundaryTrigger(boundary, position) {
  this->jump_position = jump_position;
}

void ShortJumpTrigger::Trig(Chunk * chunk_ptr, PhysicalObj * obj) {
  obj->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  obj->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

  obj->setPosition(this->jump_position);
}
