/**
 * \file
 * \brief This file contains implementation of Boots
 */
#include "boots.h"
#include "actor.h"
#include "entries.h"


/**
 * Main constructor, inherited from Armor
 */
Boots::Boots(std::string name, PhysicalObj * obj, int defence) :
  Armor(name, obj, defence) {}

/**
 * Constructor without PhysicalObj, inherited from Armor
 */
Boots::Boots(std::string name, int defence) :
  Boots(name, new PhysicalObj(), defence) {}

/**
 * Wear boots on target actor
 * \param target Actor that wears boots
 */
void Boots::Wear(Actor * target) {
  target->WearBoots(this);
}

/**
 * Convert object to binary stream. The same as in Armor, except entry.
 * \param saver Serializer object
 * \return Binary stream representing this object
 */
std::stringstream * Boots::Save(Saver * saver) {
  return Armor::Save(saver, ENTRY_BOOTS);
}
