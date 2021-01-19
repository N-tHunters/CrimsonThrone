/**
 * \file
 * \brief This file contains implementation of Item
 */
#include <string>

#include "item.hpp"
#include "actor.hpp"
#include "saver.hpp"
#include "entries.hpp"


/**
 * Item constructor with all params
 * \param name Name to identify item (used in stacking)
 * \param obj Collision and physics object for item
 */
Item::Item(std::string name, PhysicalObj * obj) {
  this->name = name;
  this->obj = obj;
}

/**
 * Constructor without physical object - in this case, the body of item will be equal to empty PhysicalObj
 * \param name Name to identify item
 */
Item::Item(std::string name) :
  Item(name, new PhysicalObj()) {};

/**
 * Empty constructor - should not use it
 */
Item::Item() {}

/**
 * Get name
 * \return Name
 */
std::string Item::GetName() {
  return this->name;
}

/**
 * Get pointer to physical object
 * \return Pointer to physical object
 */
PhysicalObj* Item::GetPhysicalObj() {
  return this->obj;
}

/**
 * Set name
 * \param name New name
 */
void Item::SetName(std::string name) {
  this->name = name;
}

/**
 * Check if the item is wearable.
 * Always returns false as the base class. Used as virtual function to be overrided in child classes
 * \return Is the item wearable? (always false for base class)
 */
bool Item::IsWearable() {
  return false;
}

/**
 * Check if the item is usable.
 * Always returns false as the base class. Used as virtual function to be overrided in child classes
 * \return Is the item usable? (always false for base class)
 */
bool Item::IsUsable() {
  return false;
}

/**
 * Check if the item is stackable.
 * Always returns false as the base class. Used as virtual function to be overrided in child classes
 * \return Is the item stackable? (always false for base class)
 */
bool Item::IsStackable() {
  return false;
}

/**
 * Use this item by actor. Not implemented in base class
 * \param Pointer to actor that tried to use this item
 */
void Item::Use(Actor *) {}

/**
 * Wear this item by actor. Not implemented in base class
 * \param Pointer to actor that tried to wear this item
 */
void Item::Wear(Actor *) {}

/**
 * Save item as binary object. This function is called by the saver and calls Item::Save(Saver * saver, int entry) function with entry.
 * \param saver Pointer to saver for saving this item
 * \return Binary stream with strored item
 */
std::stringstream * Item::Save(Saver * saver) {
  return this->Save(saver, ENTRY_ITEM);
}

/**
 * Save item as binary object. Saves item name only.
 * \param saver Pointer to saver for saving this item
 * \param entry Header of binary object
 * \return Binary stream with stored item
 */
std::stringstream * Item::Save(Saver * saver, int entry) {
  std::stringstream * ss = new std::stringstream();
  
  saver->SaveInt(ss, entry);
  saver->SaveString(ss, this->name);
  
  return ss;
}

/**
 * Get values to be shown in list
 * \return Pointer to vector of values casted to string
 */
std::vector<std::string>* Item::getValues() {
  std::vector<std::string> * values = new std::vector<std::string>();
  values->push_back(this->name);
  return values;
}
