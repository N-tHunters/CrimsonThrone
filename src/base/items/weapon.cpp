/**
 * \file
 * \brief This file contains implementation of Weapon
 */
#include <base/items/weapon.hpp>
#include <base/entries.hpp>
#include <base/saver.hpp>

/**
 * Basic constructor
 * \param name Name of this Item
 * \param obj Physical representation
 * \param damage Damage can be dealt
 * \param range Maxium distance of hit
 */
Weapon::Weapon(std::string name, PhysicalObj * obj, int damage, int range) :
  Item(name, obj) {
  this->damage = damage;
  this->range = range;
}

/**
 * Shortened constructor with empty PhysicalObj
 * \param name Name of this Item
 * \param damage Damage can be dealt
 * \param range Maxium distance of hit
 */
Weapon::Weapon(std::string name, int damage, int range) :
  Weapon(name, new PhysicalObj(), damage, range) {}

/**
 * Empty constructor
 * \warning Should not use!
 */
Weapon::Weapon() {}

/**
 * Get damage can be dealt by this weapon
 * \return Damage can be dealt
 */
int Weapon::GetDamage() {
  return this->damage;
}

/**
 * Get maximum distance
 * \return Maximum distance
 */
int Weapon::GetRange() {
  return this->range;
}

/**
 * Set damage that can be dealt
 * \param damage New damage
 */
void Weapon::SetDamage(int damage) {
  this->damage = damage;
}

/**
 * Set maximum distance of hit
 * \param range New maximum distance
 */
void Weapon::SetRange(int range) {
  this->range = range;
}

/**
 * Convert object to binary stream
 * \param saver Serializer object
 * \param entry Identifier for binary representation
 * \return Binary stream representing this object
 */
std::stringstream * Weapon::Save(Saver * saver, int entry) {
  std::stringstream * ss = Item::Save(saver, entry);
  saver->SaveInt(ss, this->damage);
  saver->SaveInt(ss, this->range);
  return ss;
}

/**
 * Convert object to binary stream with default identifier
 * \param saver Serializer object
 * \return Binary stream representing this object
 */
std::stringstream * Weapon::Save(Saver * saver) {
  return this->Save(saver, ENTRY_WEAPON);
}
