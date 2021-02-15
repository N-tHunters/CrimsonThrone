#pragma once

#include "protocore.h"

const char CORE_ID_WORLD = 0;

class WorldMagicCore : public ProtoMagicCore {  
 public:
  WorldMagicCore();
  char Call(char, char, AbstractCore *);
  PhysicalObj * GetPhyiscalObj();
};

