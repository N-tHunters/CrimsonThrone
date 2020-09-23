#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <sstream>

#include "../physics/physicsObj.h"

class Actor;
class Saver;

class Item {
private:
  std::string name;

  std::string LogDescribe();

  PhysicalObj obj;

public:
  Item(std::string, PhysicalObj);
  Item();
  
  std::string GetName();
  PhysicalObj* GetPhysicalObj();
  
  void SetName(std::string);
  void SetPhysicalObj();

  virtual bool IsUsable();
  virtual bool IsWearable();
  virtual bool IsStackable();

  virtual void Wear(Actor *);
  virtual void Use(Actor *);

  virtual std::stringstream Save(Saver *);
  virtual std::stringstream Save(Saver *, int);
};

#endif
  
