#include "boundarytrigger.hpp"

BoundaryTrigger::BoundaryTrigger(Boundary * boundary, glm::vec3 position) : Trigger() {
  this->boundary = boundary;
  this->position = position;
}

Boundary* BoundaryTrigger::GetBoundary() { return this->boundary; }
glm::vec3 BoundaryTrigger::GetPosition() { return this->position; }

