#include "armor.h"
#include "item.h"
#include "entries.h"
#include <string>

Armor::Armor(std::string name, PhysicalObj obj, int defence) :
  Item(name, obj) {
  this->defence = defence;
}

Armor::Armor() {}

int Armor::GetDefence() {
  return this->defence;
}

void Armor::SetDefence(int defence) {
  this->defence = defence;
}

bool Armor::IsWearable() {
  return true;
}

std::stringstream Armor::Save(Saver * saver, int entry) {
  std::stringstream ss = Item::Save(saver, entry);
  saver->SaveInt(&ss, this->defence);
  return ss;
}

std::stringstream Armor::Save(Saver * saver) {
  return this->Save(saver, ENTRY_ARMOR);
}
