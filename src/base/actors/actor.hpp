/**
 * \file
 * \brief This file contains declaration of Actor
 */
#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <sstream>
#include <vector>

#include <physics/physicalObj.hpp>

class Item;
class StackableItem;
class Weapon;
class Helmet;
class Gloves;
class Chestplate;
class Leggins;
class Boots;

class Saver;

/**
 * \brief Game actor class
 * \author ArturLukianov
 * 
 * This class represents base of every game character. It serves as a parent class for Player, NPC, etc.
 */

class Actor {
private:
  int health;
  int max_health;

  std::vector<Item *> inventory;

  Weapon* weapon;

  Helmet* helmet;
  Boots* boots;
  Gloves* gloves;
  Chestplate* chestplate;
  Leggins* leggins;

  std::string name;

  PhysicalObj * obj;

	
  void JustifyHealth();

public:
  Actor();
  Actor(std::string, int, PhysicalObj *);

  virtual void Process(float dt);

  int GetHealth();
  int GetMaxHealth();
  int * GetHealthPtr();
  int * GetMaxHealthPtr();

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

  void SetPhysicalObj(PhysicalObj *);

  void WearWeapon(Weapon*);
  void WearHelmet(Helmet*);
  void WearGloves(Gloves*);
  void WearChestplate(Chestplate*);
  void WearBoots(Boots*);
  void WearLeggins(Leggins*);

  int GetDefence();
  int GetDamage();
  void DealDamage(int);
  void Heal(int);

  size_t GetInventorySize();
  std::vector<Item*>* GetInventoryPointer();
  Item * GetItemAt(size_t);
  void SetItemAt(size_t, Item *);
  int GetEmptyCell();
  bool PickupItem(Item *);
  void DeleteItem(Item *);

  StackableItem * FindCompatibleItem(Item *);
  int GetItemIndex(Item *);

  std::stringstream * Save(Saver *);
};
#endif
