#include "chestplate.h"
#include "actor.h"
#include "entries.h"


Chestplate::Chestplate(std::string name, PhysicalObj obj, int defence) :
  Armor(name, obj, defence) {}

Chestplate::Chestplate(std::string name, int defence) :
  Chestplate(name, PhysicalObj(), defence) {}

void Chestplate::Wear(Actor * target) {
  target->WearChestplate(this);
}

std::stringstream * Chestplate::Save(Saver * saver) {
  return Armor::Save(saver, ENTRY_CHESTPLATE);
}
