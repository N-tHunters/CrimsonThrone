/**
 * \file
 * \brief This file contains implementation of Actor
 */
#include <string>

#include "actor.hpp"
#include "weapon.hpp"
#include "helmet.hpp"
#include "boots.hpp"
#include "chestplate.hpp"
#include "leggins.hpp"
#include "gloves.hpp"
#include "item.hpp"
#include "stackableitem.hpp"
#include "saver.hpp"


/**
 * Empty constructor
 */
Actor::Actor() {}

/**
 * Basic constructor
 * \param name Actor Name
 * \param max_health Maximum health
 * \param obj Physical object (body)
 */
Actor::Actor(std::string name, int max_health, PhysicalObj * obj) : Actor() {
  this->name = name;
  this->max_health = max_health;
  this->health = max_health;
  this->obj = obj;
}

// Getters

/**
 * Get name
 * \return Name
 */
std::string Actor::GetName() { return this->name; }

/**
 * Get current health
 * \return Current health
 */
int Actor::GetHealth() { return this->health; }

/**
 * Get pointer to current health
 * \note Useful for UI
 * \return &health Pointer to current health
 */
int * Actor::GetHealthPtr() { return &this->health; }

/**
 * Get maximum health
 * \return_health Maximum health
 */
int Actor::GetMaxHealth() { return this->max_health; }

/**
 * Get pointer to maximum health
 * \note Useful for UI
 * \return Pointer to maxium health
 */
int * Actor::GetMaxHealthPtr() { return &max_health; }

/**
 * Get pointer to weapon used by this actor
 * \return Pointer to weapon used by this actor
 */
Weapon* Actor::GetWeapon() { return weapon; }

/**
 * Get pointer to helmet used by this actor
 * \return Pointer to helmet used by this actor
 */
Helmet* Actor::GetHelmet() { return helmet; }

/**
 * Get pointer to boots used by this actor
 * \return Pointer to boots used by this actor
 */
Boots* Actor::GetBoots() { return boots; }

/**
 * Get pointer to leggins used by this actor
 * \return Pointer to leggins used by this actor
 */
Leggins* Actor::GetLeggins() { return leggins; }

/**
 * Get pointer to gloves used by this actor
 * \return Pointer to gloves used by this actor 
 */
Gloves* Actor::GetGloves() { return gloves; }

/**
 * Get pointer to chestplate used by this actor
 * \return Pointer to chestplate used by this actor
 */
Chestplate* Actor::GetChestplate() { return chestplate; }

/**
 * Get pointer to physical object (body) used by this actor
 * \return Pointer to physical object used by this actor
 */
PhysicalObj* Actor::GetPhysicalObj() { return obj; }


/**
 * Set name to this actor
 * \param name New name
 */
void Actor::SetName(std::string name) { this->name = name; }

/**
 * Set current health to this actor
 * \param health New value of health
 */
void Actor::SetHealth(int health) { this->health = health; }

/**
 * Set maximum health to this actor
 * \param max_health New value of maximum health
 */
void Actor::SetMaxHealth(int max_health) { this->max_health = max_health; }

/**
 * Set weapon to use
 * \param weapon Pointer to new weapon to use
 */
void Actor::SetWeapon(Weapon* weapon) { this->weapon = weapon; }

/**
 * Set helmet to use
 * \param helmet Pointer to new helmet to use
 */
void Actor::SetHelmet(Helmet* helmet) { this->helmet = helmet; }

/**
 * Set boots to use
 * \param boots Pointer to new boots to use
 */
void Actor::SetBoots(Boots* boots) { this->boots = boots; }

/**
 * Set gloves to use
 * \param gloves Pointer to new gloves to use
 */
void Actor::SetGloves(Gloves* gloves) { this->gloves = gloves; }

/**
 * Set chestplate to use
 * \param chestplate Pointer to new gloves to use
 */
void Actor::SetChestplate(Chestplate* chestplate) { this->chestplate = chestplate; }

/**
 * Set leggins to use
 * \param leggins Pointer to new leggins to use
 */
void Actor::SetLeggins(Leggins* leggins) { this->leggins = leggins; }

/**
 * Set physical object
 * \param obj Pointer to new physical object
 */
void Actor::SetPhysicalObj(PhysicalObj* obj) { this->obj = obj; }

/**
 * Wear weapon (Same as Set* functions)
 * \param weapon Pointer to weapon to wear
 */
void Actor::WearWeapon(Weapon* weapon) {
  this->SetWeapon(weapon);
}

/**
 * Wear gloves (Same as Set* functions)
 * \param gloves Pointer to gloves to wear
 */
void Actor::WearHelmet(Helmet* helmet) {
  this->SetHelmet(helmet);
}

/**
 * Wear weapon (Same as Set* functions)
 * \param weapon Pointer to weapon to wear
 */
void Actor::WearGloves(Gloves* gloves) {
  this->SetGloves(gloves);
}

/**
 * Wear boots (Same as Set* functions)
 * \param boots Pointer to boots to wear
 */
void Actor::WearBoots(Boots* boots) {
  this->SetBoots(boots);
}

/**
 * Wear chestplate (Same as Set* functions)
 * \param chestplate Pointer to chestplate to wear
 */
void Actor::WearChestplate(Chestplate* chestplate) {
  this->SetChestplate(chestplate);
}

/**
 * Wear leggins (Same as Set* functions)
 * \param leggins Pointer to leggins to wear
 */
void Actor::WearLeggins(Leggins* leggins) {
  this->SetLeggins(leggins);
}


/**
 * Set health to maximum, if above
 */
void Actor::JustifyHealth() {
  this->health = std::min(this->health, this->max_health);
}
/**
 * Get sumary defence of all armor
 */
int Actor::GetDefence() {
  return this->helmet->GetDefence() +
    this->boots->GetDefence() +
    this->gloves->GetDefence() +
    this->chestplate->GetDefence() +
    this->leggins->GetDefence();
}

/**
 * Get damage can be dealt by weapon
 */
int Actor::GetDamage() {
  return this->weapon->GetDamage();
}

/**
 * Add some amount of health
 * \param amount Amount of health to restore
 */
void Actor::Heal(int amount) {
  this->health += amount;
  this->JustifyHealth();
}

/**
 * Substract some amount of health
 * \param amount Amount of health to substract
 */
void Actor::DealDamage(int amount) {
  this->health -= amount;
}

/**
 * Get item at position
 * \param index Position of item (from 0 to inventory size)
 */
Item * Actor::GetItemAt(size_t index) {
  if (index >= this->GetInventorySize())
    return nullptr;
  return this->inventory[index];
}

/**
 * Set item at position
 * \param index Position of item that will be replaced
 * \param item Pointer to item that will be placed at index
 */
void Actor::SetItemAt(size_t index, Item * item) {
  if (index >= this->GetInventorySize())
    return;
  this->inventory[index] = item;
}

/**
 * Get first empty cell of inventory or -1 if inventory is full
 */
int Actor::GetEmptyCell() {
  for(size_t i = 0; i < this->GetInventorySize(); i++) {
    if(this->inventory[i] == nullptr) {
      return i;
    }
  }
  return -1;
}

/**
 * Find item can be stacked with supplied exemplar
 * \param item Exemplar
 */
StackableItem * Actor::FindCompatibleItem(Item * item) {
  for(size_t i = 0; i < this->GetInventorySize(); i++) {
    if(this->inventory[i] != nullptr &&
       this->inventory[i]->IsStackable() &&
       this->inventory[i]->GetName() == item->GetName())
      {
	return (StackableItem *)this->inventory[i];
      }
  }
  return nullptr;
}

/**
 * Put item in empty cell if exists, if not return false
 * \param item Pointer to item to pick up
 */
bool Actor::PickupItem(Item * item) {
  if(item->IsStackable()) {
    StackableItem * compatible = this->FindCompatibleItem(item);
    if (compatible != nullptr) {
      compatible->Stack((StackableItem *)item);
      return true;
    }
  }
  int index = this->GetEmptyCell();
  if (index < 0)
    this->inventory.push_back(item);
  else 
    this->SetItemAt(index, item);
  return true;
}

/**
 * Get current inventory size
 * \returns Size of inventory
 */
size_t Actor::GetInventorySize() {
  return this->inventory.size();
}

/**
 * Get pointer to inventory
 * \note Useful for UI
 */
std::vector<Item*>* Actor::GetInventoryPointer() {
  return &(this->inventory);
}

/**
 * Delete item from inventory
 * \param item Pointer to item to delete
 */
void Actor::DeleteItem(Item * item) {
  int index = this->GetItemIndex(item);
  if (index >= (signed int)this->GetInventorySize())
    return;
  if (index < 0)
    return;
  this->inventory.erase(this->inventory.begin() + index);
}


/**
 * Get index of item or -1 if item is not in inventory
 * \param item poinrter to item to find in inventory
 * \return -1 if item is not in inventory or index of that item
 */
int Actor::GetItemIndex(Item * item) {
  for(size_t i = 0; i < this->GetInventorySize(); i ++) {
    if(this->inventory[i] == item) {
      return i;
    }
  }
  return -1;
}


/**
 * Convert Actor to binary stream
 * Saves name, health, maximum health, inventory, weapon and armor
 * \param saver Serializer object
 * \return Binary stream representing object
 */
std::stringstream * Actor::Save(Saver * saver) {
  std::stringstream * ss = new std::stringstream();

  saver->SaveString(ss, this->name);
  saver->SaveInt(ss, health);
  saver->SaveInt(ss, max_health);
  for(size_t i = 0; i < this->GetInventorySize(); i++) {
    if (this->inventory[i] != nullptr)
      saver->SaveItem(ss, this->inventory[i]);
  }

  saver->SaveItem(ss, this->weapon);
  saver->SaveItem(ss, this->helmet);
  saver->SaveItem(ss, this->boots);
  saver->SaveItem(ss, this->gloves);
  saver->SaveItem(ss, this->chestplate);
  saver->SaveItem(ss, this->leggins);

  return ss;
}
