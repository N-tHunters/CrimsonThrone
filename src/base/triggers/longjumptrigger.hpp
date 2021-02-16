#ifndef LONG_JUMP_TRIGGER_H
#define LONG_JUMP_TRIGGER_H

#include <base/triggers/shortjumptrigger.hpp>
#include <base/location/location.hpp>

class LongJumpTrigger : public ShortJumpTrigger {
  Location * location;
  Chunk * chunk;
 public:
  LongJumpTrigger(Boundary *, glm::vec3, glm::vec3, Chunk *);
  LongJumpTrigger(PhysicalObj *, glm::vec3, Chunk *);
  virtual void Trig(Chunk *, PhysicalObj *) override;
  virtual void TrigPlayer(Chunk *, PhysicalObj *) override;
};

#endif
