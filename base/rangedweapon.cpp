#include "rangedweapon.h"
#include "actor.h"
#include "missle.h"
#include "entries.h"

Missle* RangedWeapon::GetMissle() {
  return this->missle;
}

void RangedWeapon::SetMissle(Missle *missle) {
  this->missle = missle;
}

void RangedWeapon::UseMissle(Actor * target) {
  this->missle->Use(target);
}

std::stringstream RangedWeapon::Save(Saver * saver) {
  std::stringstream ss = Weapon::Save(saver, ENTRY_RANGED);
  saver->SaveItem(&ss, this->missle);
  return ss;
}
