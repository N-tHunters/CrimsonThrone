#ifndef BOOTS_H
#define BOOTS_H

#include "armor.h"
#include "saver.h"
#include "../physics/physicalObj.h"
#include <sstream>

class Actor;

class Boots : public Armor {
public:
  Boots(std::string, PhysicalObj, int);
  Boots(std::string, int);
  void Wear(Actor *);

  std::stringstream Save(Saver *);
};

#endif
