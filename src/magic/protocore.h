#pragma once

#include "abscore.h"
#include <map>

class ProtoMagicCore : public AbstractCore {
 public:
  ProtoMagicCore();
  ProtoMagicCore(PhysicalObj*);
  virtual char Call(char, char, AbstractCore *);
};

char proto_call(char, char, char, AbstractCore *);
void init_protocores();

