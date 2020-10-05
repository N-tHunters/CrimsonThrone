#ifndef LEGGINS_H
#define LEGGINS_H

#include "armor.h"
#include "saver.h"
#include "../physics/physicalObj.h"
#include <sstream>

class Actor;

class Leggins : public Armor {
public:
  Leggins(std::string, PhysicalObj, int);
  Leggins(std::string, int);
  void Wear(Actor *);

  std::stringstream * Save(Saver *);
};

#endif
