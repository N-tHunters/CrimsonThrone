#include "helmet.h"
#include "actor.h"
#include "entries.h"

Helmet::Helmet(std::string name, PhysicalObj obj, int defence) :
  Armor(name, obj, defence) {}

void Helmet::Wear(Actor * target) {
  target->WearHelmet(this);
}


std::stringstream Helmet::Save(Saver * saver) {
  return Armor::Save(saver, ENTRY_HELMET);
}
