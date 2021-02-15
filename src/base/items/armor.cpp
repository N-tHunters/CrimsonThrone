/**
 * \file
 * \brief This file contains implementation of Armor
 */
#include <base/items/armor.hpp>
#include <base/items/item.hpp>
#include <base/entries.hpp>
#include <string>

/**
 * Basic armor constructor
 * \param name Name
 * \param obj Physical object
 * \param defence Defence given by that piece of armor
 */
Armor::Armor(std::string name, PhysicalObj  * obj, int defence) :
  Item(name, obj) {
  this->defence = defence;
}

/**
 * Construct armor with empty physical object
 */
Armor::Armor(std::string name, int defence) :
  Armor(name, new PhysicalObj(), defence) {}

/**
 * Empty constructor
 * \warning Should not use
 */
Armor::Armor() {}

/**
 * Get defence
 * \return Amount of defence given by that piece of armor
 */
int Armor::GetDefence() { return defence; }

/**
 * Set defence
 * \param defence Amount of defence will be given by that piece of armor
 */
void Armor::SetDefence(int defence) {
  this->defence = defence;
}

/**
 * Is this piece wearable? Should always return true for armor and it's child classes
 * \returns true
 */
bool Armor::IsWearable() { return true; }

/**
 * Convert to binary stream. Calls Item::Save(Saver *, int) and additionally stores amount of defence
 * \param saver Serializer object
 * \param entry Type of object to save (Something like tag)
 * \return Binary stream representing this object
 */
std::stringstream * Armor::Save(Saver * saver, int entry) {
  std::stringstream * ss = Item::Save(saver, entry);
  saver->SaveInt(ss, this->defence);
  return ss;
}

/**
 * Convert to binary stream. Short version, only for this class, not for childs.
 * \param saver Serializer object
 * \return Binary stream representing this object
 */
std::stringstream * Armor::Save(Saver * saver) { return Save(saver, ENTRY_ARMOR); }
