#ifndef SHORT_JUMP_TRIGGER
#define SHORT_JUMP_TRIGGER

#include "boundarytrigger.hpp"

class ShortJumpTrigger : public BoundaryTrigger{
  glm::vec3 jump_position;
 public:
  ShortJumpTrigger(Boundary *, glm::vec3, glm::vec3);
  ShortJumpTrigger(PhysicalObj *, glm::vec3);
  virtual void Trig(Chunk *, PhysicalObj *) override;
};

#endif
