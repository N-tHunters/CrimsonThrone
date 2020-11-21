/**
 * \file
 * \brief This file contains implementation for Chestplate
 */
#include "chestplate.h"
#include "actor.h"
#include "entries.h"


/**
 * Basic constructor implemented from Armor. Just the same.
 */
Chestplate::Chestplate(std::string name, PhysicalObj * obj, int defence) :
  Armor(name, obj, defence) {}

/**
 * Constructor without PhysicalObj. Just the same as in Armor.
 */
Chestplate::Chestplate(std::string name, int defence) :
  Chestplate(name, new PhysicalObj(), defence) {}

/**
 * Wear chestplate on target.
 * \param target Who wears chestplate
 */
void Chestplate::Wear(Actor * target) {
  target->WearChestplate(this);
}

/**
 * Convert object to binary stream.
 * \param saver Serializer
 * \return Binary stream representing this object
 */
std::stringstream * Chestplate::Save(Saver * saver) {
  return Armor::Save(saver, ENTRY_CHESTPLATE);
}
