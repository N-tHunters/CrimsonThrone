#ifndef GLOVES_H
#define GLOVES_H

#include "armor.h"
#include "saver.h"
#include "../physics/physicalObj.h"
#include <sstream>

class Gloves;

class Gloves : public Armor {
public:
  Gloves(std::string, PhysicalObj *, int);
  Gloves(std::string, int);
  void Wear(Actor *);

  std::stringstream * Save(Saver *);
};

#endif
