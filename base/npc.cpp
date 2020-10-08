#include "npc.h"

NPC::NPC() {}
NPC::NPC(std::string name, int max_health, PhysicalObj * obj) :
  Actor(name, max_health, obj) {}
