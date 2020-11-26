#ifndef ABSCORE_H
#define ABSCORE_H

#include "../../physics/physicalObj.h"

class ProtoMagicCore;

class AbstractCore {
  ProtoMagicCore * child_cores[256];
  AbstractCore * parent_core;

  char FindEmptyChildCell();

  PhysicalObj * physical_obj;
 public:
  AbstractCore();
  AbstractCore(PhysicalObj *);
  virtual PhysicalObj * GetPhysicalObj();
  void SetPhysicalObj(PhysicalObj *);
  char AddChildProtoCore(ProtoMagicCore *);
  void SetParent(AbstractCore *);
};

#endif
