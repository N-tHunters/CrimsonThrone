#ifndef SHORT_JUMP_TRIGGER
#define SHORT_JUMP_TRIGGER

#include "boundarytrigger.h"

class ShortJumpTrigger : BoundaryTrigger{
  glm::vec3 jump_position;
 public:
  ShortJumpTrigger(Boundary *, glm::vec3, glm::vec3);
  virtual void Trig(PhysicalObj *);
};

#endif
