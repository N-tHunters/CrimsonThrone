#ifndef NPC_H
#define NPC_H

#include "actor.h"

class NPC : public Actor {
 private:
 public:
  NPC();
  NPC(std::string, int, PhysicalObj *);
};

#endif
