#ifndef LONG_JUMP_TRIGGER_H
#define LONG_JUMP_TRIGGER_H

#include "shortjumptrigger.hpp"
#include "location.hpp"

class LongJumpTrigger : public ShortJumpTrigger {
  Location * location;
  Chunk * chunk;
 public:
  LongJumpTrigger(Boundary *, glm::vec3, glm::vec3, Chunk *);
  virtual void Trig(Chunk *, PhysicalObj *) override;
};

#endif