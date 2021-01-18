#ifndef OBJECTCONTROLCORE_H
#define OBJECTCONTROLCORE_H

#include "protocore.h"

class ObjectControlCore : public ProtoMagicCore {
 private:
 public:
  ObjectControlCore(PhysicalObj *);
  char SetVelocity(char arg, AbstractCore *core);
  char Call(char id, char arg, AbstractCore *core);
};

#endif
