#ifndef BOUNDARY_TRIGGER_H
#define BOUNDARY_TRIGGER_H

#include "../physics/boundary.hpp"
#include "trigger.hpp"

class BoundaryTrigger : public Trigger {
  Boundary * boundary;
  glm::vec3 position;
 public:
  BoundaryTrigger(Boundary *, glm::vec3);

  Boundary * GetBoundary();
  glm::vec3 GetPosition();
};

#endif
