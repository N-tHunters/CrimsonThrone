/**
 * \file
 * \brief This file contains implementation of Helmet
 */
#include "helmet.hpp"
#include "actor.hpp"
#include "entries.hpp"

/**
 * Basic constructor implemented from Armor. Just the same.
 */
Helmet::Helmet(std::string name, PhysicalObj * obj, int defence) :
  Armor(name, obj, defence) {}

/**
 * Constructor without PhysicalObj. Just the same as in Armor.
 */
Helmet::Helmet(std::string name, int defence) :
  Helmet(name, new PhysicalObj(), defence) {}

/**
 * Wear helmet on target.
 * \param target Who wears helmet
 */
void Helmet::Wear(Actor * target) {
  target->WearHelmet(this);
}

/**
 * Convert object to binary stream.
 * \param saver Serializer
 * \return Binary stream representing this object
 */
std::stringstream * Helmet::Save(Saver * saver) {
  return Armor::Save(saver, ENTRY_HELMET);
}
