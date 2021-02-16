#ifndef TRIGGER_H
#include <physics/physicalObj.hpp>

class Chunk;

/***
 * \brief Trigger represents action what is executed when actor gets into defined area
 */
class Trigger {
 public:
  Trigger();
  virtual void Trig(Chunk *, PhysicalObj *);
  virtual void TrigPlayer(Chunk *, PhysicalObj *);
};


#endif
