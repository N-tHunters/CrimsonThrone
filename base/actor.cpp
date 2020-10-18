#include <string>

#include "actor.h"
#include "weapon.h"
#include "helmet.h"
#include "boots.h"
#include "chestplate.h"
#include "leggins.h"
#include "gloves.h"
#include "item.h"
#include "stackableitem.h"
#include "saver.h"


Actor::Actor() {}

Actor::Actor(std::string name, int max_health, PhysicalObj * obj) : Actor() {
  this->name = name;
  this->max_health = max_health;
  this->health = max_health;
  this->obj = obj;
}

// Getters
std::string Actor::GetName() {
  return this->name;
}

int Actor::GetHealth() {
  return this->health;
}

int * Actor::GetHealthPtr() {
  return &this->health;
}

int Actor::GetMaxHealth() {
  return this->max_health;
}

int * Actor::GetMaxHealthPtr() {
  return &this->max_health;
}

Weapon* Actor::GetWeapon() {
  return this->weapon;
}

Helmet* Actor::GetHelmet() {
  return this->helmet;
}

Boots* Actor::GetBoots() {
  return this->boots;
}

Leggins* Actor::GetLeggins() {
  return this->leggins;
}

Gloves* Actor::GetGloves() {
  return this->gloves;
}

Chestplate* Actor::GetChestplate() {
  return this->chestplate;
}

PhysicalObj* Actor::GetPhysicalObj() {
  return this->obj;
}

// Setters
void Actor::SetName(std::string name) {
  this->name = name;
}

void Actor::SetHealth(int health) {
  this->health = health;
}

void Actor::SetMaxHealth(int max_health) {
  this->max_health = max_health;
}

void Actor::SetWeapon(Weapon* weapon) {
  this->weapon = weapon;
}

void Actor::SetHelmet(Helmet* helmet) {
  this->helmet = helmet;
}

void Actor::SetBoots(Boots* boots) {
  this->boots = boots;
}

void Actor::SetGloves(Gloves* gloves) {
  this->gloves = gloves;
}

void Actor::SetChestplate(Chestplate* chestplate) {
  this->chestplate = chestplate;
}

void Actor::SetLeggins(Leggins* leggins) {
  this->leggins = leggins;
}

void Actor::SetPhysicalObj(PhysicalObj* obj) {
  this->obj = obj;
}

// Wear functions

void Actor::WearWeapon(Weapon* weapon) {
  this->SetWeapon(weapon);
}

void Actor::WearHelmet(Helmet* helmet) {
  this->SetHelmet(helmet);
}

void Actor::WearGloves(Gloves* gloves) {
  this->SetGloves(gloves);
}

void Actor::WearBoots(Boots* boots) {
  this->SetBoots(boots);
}

void Actor::WearChestplate(Chestplate* chestplate) {
  this->SetChestplate(chestplate);
}

void Actor::WearLeggins(Leggins* leggins) {
  this->SetLeggins(leggins);
}

// Helper functions
void Actor::JustifyHealth() {
  this->health = std::min(this->health, this->max_health);
}

// Get sumary defence of all armor on Actor
int Actor::GetDefence() {
  return this->helmet->GetDefence() +
    this->boots->GetDefence() +
    this->gloves->GetDefence() +
    this->chestplate->GetDefence() +
    this->leggins->GetDefence();
}

// Get damage can be dealt by actor
int Actor::GetDamage() {
  return this->weapon->GetDamage();
}

// Add some amount of health
void Actor::Heal(int amount) {
  this->health += amount;
  this->JustifyHealth();
}

// Substract some amount of health
void Actor::DealDamage(int amount) {
  this->health -= amount;
}


// Functions to work with inventory

// Get item at position
Item * Actor::GetItemAt(int index) {
  if (index < 0)
    return nullptr;
  if (index >= this->GetInventorySize())
    return nullptr;
  return this->inventory[index];
}

// Set item at position
void Actor::SetItemAt(int index, Item * item) {
  if (index < 0)
    return;
  if (index >= this->GetInventorySize())
    return;
  this->inventory[index] = item;
}

// Get first empty cell of inventory or -1 if inventory is full
int Actor::GetEmptyCell() {
  for(int i = 0; i < this->GetInventorySize(); i++) {
    if(this->inventory[i] == nullptr) {
      return i;
    }
  }
  return -1;
}

// Find item can be stacked with supplied
StackableItem * Actor::FindCompatibleItem(Item * item) {
  for(int i = 0; i < this->GetInventorySize(); i++) {
    if(this->inventory[i] != nullptr &&
       this->inventory[i]->IsStackable() &&
       this->inventory[i]->GetName() == item->GetName())
      {
	return (StackableItem *)this->inventory[i];
      }
  }
  return nullptr;
}

// Put item in empty cell if exists, if not return false
bool Actor::PickupItem(Item * item) {
  if(item->IsStackable()) {
    StackableItem * compatible = this->FindCompatibleItem(item);
    if (compatible != nullptr) {
      compatible->Stack((StackableItem *)item);
      return true;
    }
  }
  int index = this->GetEmptyCell();
  if (index < 0) {
    this->inventory.push_back(item);
  } else 
    this->SetItemAt(index, item);
  return true;
}

int Actor::GetInventorySize() {
  return this->inventory.size();
}

// Delete item from inventory
void Actor::DeleteItem(Item * item) {
  int index = this->GetItemIndex(item);
  if (index >= this->GetInventorySize())
    return;
  if (index < 0)
    return;
  this->inventory.erase(this->inventory.begin() + index);
}


// Get index of item or -1
int Actor::GetItemIndex(Item * item) {
  for(int i = 0; i < this->GetInventorySize(); i ++) {
    if(this->inventory[i] == item) {
      return i;
    }
  }
  return -1;
}


std::stringstream * Actor::Save(Saver * saver) {
  std::stringstream * ss = new std::stringstream();

  saver->SaveString(ss, this->name);
  saver->SaveInt(ss, health);
  saver->SaveInt(ss, max_health);
  for(int i = 0; i < this->GetInventorySize(); i++) {
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
