/**
 * \file
 * \brief This file contains implementaion of Gloves
 */
#include "gloves.hpp"
#include "actor.hpp"
#include "entries.hpp"

/// Basic constructor inherited from Armor
Gloves::Gloves(std::string name, PhysicalObj * obj, int defence) :
  Armor(name, obj, defence) {}

/// Contructor without PhysicalObj
Gloves::Gloves(std::string name, int defence) :
  Gloves(name, new PhysicalObj(), defence) {}

/**
 * Wear gloves on target
 * \param target Who wears gloves
 */
void Gloves::Wear(Actor * target) {
  target->WearGloves(this);
}

/**
 * Convert object to binary stream represening this object
 * \param saver Serializer
 * \return Binary stream
 */
std::stringstream * Gloves::Save(Saver * saver) {
  return Armor::Save(saver, ENTRY_GLOVES);
}

