#ifndef BOUNDARY_TRIGGER_H
#define BOUNDARY_TRIGGER_H

#include <physics/boundary.hpp>
#include "trigger.hpp"

class BoundaryTrigger : public Trigger {
  BoundaryBox * boundary;
  glm::vec3 position;
  PhysicalObj * link;
 public:
  BoundaryTrigger(BoundaryBox *, glm::vec3);
  BoundaryTrigger(PhysicalObj *);

  BoundaryBox * GetBoundary();
  glm::vec3 GetPosition();
  PhysicalObj * GetLink();
};

#endif
