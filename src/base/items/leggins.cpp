/**
 * \file
 * \brief This file contains implementation of Leggins
 */
#include <base/items/leggins.hpp>
#include <base/actors/actor.hpp>
#include <base/entries.hpp>

/**
 * Basic constructor implemented from Armor. Just the same.
 */
Leggins::Leggins(std::string name, PhysicalObj * obj, int defence) :
  Armor(name, obj, defence) {}

/**
 * Constructor without PhysicalObj. Just the same as in Armor.
 */
Leggins::Leggins(std::string name, int defence) :
  Leggins(name, new PhysicalObj(), defence) {}

/**
 * Wear leggins on target.
 * \param target Who wears leggins
 */
void Leggins::Wear(Actor* target) {
  target->WearLeggins(this);
}

/**
 * Convert object to binary stream.
 * \param saver Serializer
 * \return Binary stream representing this object
 */
std::stringstream * Leggins::Save(Saver * saver) {
  return Armor::Save(saver, ENTRY_LEGGINS);
}
