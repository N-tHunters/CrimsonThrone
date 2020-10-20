#include "leggins.h"
#include "actor.h"
#include "entries.h"

Leggins::Leggins(std::string name, PhysicalObj * obj, int defence) :
  Armor(name, obj, defence) {}

Leggins::Leggins(std::string name, int defence) :
  Leggins(name, new PhysicalObj(), defence) {}

void Leggins::Wear(Actor* target) {
  target->WearLeggins(this);
}

std::stringstream * Leggins::Save(Saver * saver) {
  return Armor::Save(saver, ENTRY_LEGGINS);
}
