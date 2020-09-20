#include "boots.h"
#include "actor.h"
#include "entries.h"

Boots::Boots(std::string name, int defence) :
  Armor(name, defence) {}

void Boots::Wear(Actor * target) {
  target->WearBoots(this);
}

std::stringstream Boots::Save(Saver * saver) {
  return Armor::Save(saver, ENTRY_BOOTS);
}
