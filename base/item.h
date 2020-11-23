/**
 * \file
 * \brief This file contains declaration of Item
 */
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <sstream>

#include "../physics/physicalObj.h"
#include "../UI/abstractListElement.h"

class Actor;
class Saver;

/**
 * \brief This class represent base for pickable and usable game objects. (Like HealPotion or Weapon).
 * \author ArturLukianov
 * 
 * This class represent base for pickable and usable game objects like HealPotion and Weapon. Inherit it or it's child objects to implement new type of game item
 */
class Item : public AbstractListElement {
private:
  std::string name;

  PhysicalObj * obj;

public:
  Item(std::string, PhysicalObj *);
  Item(std::string);
  Item();
  
  std::string GetName();
  PhysicalObj* GetPhysicalObj();
  
  void SetName(std::string);

  virtual bool IsUsable();
  virtual bool IsWearable();
  virtual bool IsStackable();

  virtual void Wear(Actor *);
  virtual void Use(Actor *);

  virtual std::stringstream * Save(Saver *);
  virtual std::stringstream * Save(Saver *, int);

  virtual std::vector<std::string>* getValues();
};

#endif
  
