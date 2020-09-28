#ifndef CHESTPLATE_H
#define CHESTPLATE_H

#include "armor.h"
#include "saver.h"
#include "../physics/physicalObj.h"
#include <sstream>

class Actor;

class Chestplate : public Armor {
public:
  Chestplate(std::string, PhysicalObj, int);
  void Wear(Actor *);

  std::stringstream Save(Saver *);
};

#endif
