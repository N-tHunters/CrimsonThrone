#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"
#include "saver.h"
#include "../physics/physicalObj.h"
#include <sstream>

class Weapon : public Item {
private:
  int damage;
  int range;

public:
  Weapon(std::string, PhysicalObj *, int, int);
  Weapon(std::string, int, int);
  Weapon();
  int GetDamage();
  int GetRange();

  void SetDamage(int);
  void SetRange(int);

  virtual std::stringstream * Save(Saver *);
  std::stringstream * Save(Saver *, int);
};

#endif
