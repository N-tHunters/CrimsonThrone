#ifndef TRIGGER_H
#include "../physics/physicalObj.hpp"

/***
 * \brief Trigger represents action what is executed when actor gets into defined area
 */
class Trigger {
 public:
  Trigger();
  virtual void Trig(PhysicalObj *);
};


#endif
