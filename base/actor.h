#ifndef ACTOR_H
#define ACTOR_H

#define INVENTORY_SIZE 100

#include <string>
#include <sstream>

#include "../physics/physicalObj.h"

class Item;
class StackableItem;
class Weapon;
class Helmet;
class Gloves;
class Chestplate;
class Leggins;
class Boots;

class Saver;

class Actor {
 private:
  int health;
  int max_health;

  Item* inventory[INVENTORY_SIZE];

  Weapon* weapon;

  Helmet* helmet;
  Boots* boots;
  Gloves* gloves;
  Chestplate* chestplate;
  Leggins* leggins;

  std::string name;

  PhysicalObj obj;

  
  // Helper functions
  void JustifyHealth(); // Check if health is over max_health and justify it

 public:
  Actor();
  Actor(std::string, int, PhysicalObj);
  // Getters
  int GetHealth();
  int GetMaxHealth();

  std::string GetName();

  Weapon* GetWeapon();
  Helmet* GetHelmet();
  Gloves* GetGloves();
  Chestplate* GetChestplate();
  Boots* GetBoots();
  Leggins* GetLeggins();

  PhysicalObj* GetPhysicalObj();

  // Setters
  void SetHealth(int);
  void SetMaxHealth(int);
  
  void SetName(std::string);

  void SetWeapon(Weapon*);
  void SetHelmet(Helmet*);
  void SetGloves(Gloves*);
  void SetChestplate(Chestplate*);
  void SetBoots(Boots*);
  void SetLeggins(Leggins*);

  void SetPhysicalObj(PhysicalObj);

  void WearWeapon(Weapon*);
  void WearHelmet(Helmet*);
  void WearGloves(Gloves*);
  void WearChestplate(Chestplate*);
  void WearBoots(Boots*);
  void WearLeggins(Leggins*);

  int GetDefence(); // Get summary defence of all armor
  int GetDamage(); // Get damage (shortcut for .GetWeapon().GetDamage)
  void DealDamage(int); // Substract health
  void Heal(int); // Add health maximum to max_health

  // Functions to work with Inventory
  Item * GetItemAt(int);
  void SetItemAt(int, Item *);
  int GetEmptyCell();
  bool PickupItem(Item *);
  void DeleteItem(Item *);

  StackableItem * FindCompatibleItem(Item *);
  int GetItemIndex(Item *);

  std::stringstream Save(Saver *);
};
#endif
