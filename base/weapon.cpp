#include "weapon.h"
#include "entries.h"
#include "saver.h"

Weapon::Weapon(std::string name, PhysicalObj obj, int damage, int range) :
  Item(name, obj) {
  this->damage = damage;
  this->range = range;
}

Weapon::Weapon() {}

int Weapon::GetDamage() {
  return this->damage;
}

int Weapon::GetRange() {
  return this->range;
}

void Weapon::SetDamage(int damage) {
  this->damage = damage;
}

void Weapon::SetRange(int range) {
  this->range = range;
}

std::stringstream Weapon::Save(Saver * saver, int entry) {
  std::stringstream ss = Item::Save(saver, entry);
  saver->SaveInt(&ss, this->damage);
  saver->SaveInt(&ss, this->range);
  return ss;
}

std::stringstream Weapon::Save(Saver * saver) {
  return this->Save(saver, ENTRY_WEAPON);
}
