#include "gloves.h"
#include "actor.h"
#include "entries.h"


Gloves::Gloves(std::string name, int defence) :
  Armor(name, defence) {}

void Gloves::Wear(Actor * target) {
  target->WearGloves(this);
}

std::stringstream Gloves::Save(Saver * saver) {
  return Armor::Save(saver, ENTRY_GLOVES);
}
