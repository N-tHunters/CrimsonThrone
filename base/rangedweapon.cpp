/**
 * \file
 * \brief This file contains implementation of RangedWeapon
 */
#include "rangedweapon.h"
#include "actor.h"
#include "missle.h"
#include "entries.h"

/**
 * Get missle used by this weapon
 * \return Missle used by this weapon
 */
Missle* RangedWeapon::GetMissle() {
  return this->missle;
}

/**
 * Set misssle to use with this weapon
 * \param missle New missle
 */
void RangedWeapon::SetMissle(Missle *missle) {
  this->missle = missle;
}

/**
 * Use missle of this weapon (decrease its amount in stack)
 * \param target Use missle of target
 */
void RangedWeapon::UseMissle(Actor * target) {
  this->missle->Use(target);
}

/**
 * Convert object to binary stream.
 * \param saver Serializer
 * \return Binary stream representing this object
 */
std::stringstream * RangedWeapon::Save(Saver * saver) {
  std::stringstream * ss = Weapon::Save(saver, ENTRY_RANGED);
  saver->SaveItem(ss, this->missle);
  return ss;
}
