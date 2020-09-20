#ifndef HELMET_H
#define HELMET_H

#include "armor.h"
#include "saver.h"
#include <string>
#include <sstream>

class Actor;

class Helmet : public Armor {
public:
  Helmet(std::string, int);
  void Wear(Actor *);

  std::stringstream Save(Saver *);
};

#endif
