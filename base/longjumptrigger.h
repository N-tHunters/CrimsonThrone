#ifndef LONG_JUMP_TRIGGER_H
#define LONG_JUMP_TRIGGER_H

#include "shortjumptrigger.h"
#include "location.h"

class LongJumpTrigger : public ShortJumpTrigger {
  Location * location;
  Chunk * chunk;
 public:
  LongJumpTrigger(Boundary *, glm::vec3, glm::vec3, Location*, Chunk *);
  void Trig(PhysicalObj *) override;
};

#endif
