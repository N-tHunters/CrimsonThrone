#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <sstream>

#include "../physics/physicalObj.h"

class Actor;
class Saver;

class Item {
private:
  std::string name;

  PhysicalObj obj;

  std::string LogDescribe();

public:
  Item(std::string, PhysicalObj);
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

  virtual std::stringstream Save(Saver *);
  virtual std::stringstream Save(Saver *, int);
};

#endif
  
