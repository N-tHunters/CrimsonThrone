#include "boots.h"
#include "actor.h"
#include "entries.h"

Boots::Boots(std::string name, PhysicalObj obj, int defence) :
  Armor(name, obj, defence) {}

void Boots::Wear(Actor * target) {
  target->WearBoots(this);
}

std::stringstream Boots::Save(Saver * saver) {
  return Armor::Save(saver, ENTRY_BOOTS);
}
