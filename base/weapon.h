/**
 * \file
 * \brief This file contains declaration of Weapon
 */
#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"
#include "saver.h"
#include <sstream>

/**
 * \brief Weapon is Item dedicated to deal damage by hitting the target
 */
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
