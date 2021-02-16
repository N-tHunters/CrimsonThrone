#include "trigger.hpp"

Trigger::Trigger() {}
void Trigger::Trig(Chunk *, PhysicalObj *) {}

void Trigger::TrigPlayer(Chunk * chunk, PhysicalObj * po) {
  Trig(chunk, po);
}
