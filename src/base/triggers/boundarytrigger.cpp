#include "boundarytrigger.hpp"

BoundaryTrigger::BoundaryTrigger(Boundary * boundary, glm::vec3 position) : Trigger() {
  this->boundary = boundary;
  this->position = position;
  this->link = nullptr;
}

BoundaryTrigger::BoundaryTrigger(PhysicalObj * link) : Trigger() {
  this->boundary = new BoundaryBox(((BoundaryBox*)link->boundary)->width + 0.1f,
				   ((BoundaryBox*)link->boundary)->height + 0.1f,
				   ((BoundaryBox*)link->boundary)->length + 0.1f);
  this->position = link->getPosition();
  this->link = link;
}

Boundary* BoundaryTrigger::GetBoundary() { return this->boundary; }
glm::vec3 BoundaryTrigger::GetPosition() { return this->position; }
PhysicalObj * BoundaryTrigger::GetLink() { return this->link; }
