/**
 * \file
 * \brief This file contains declaration of Weapon
 */
#ifndef WEAPON_H
#define WEAPON_H

#include <base/items/item.hpp>
#include <base/saver.hpp>
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

  void Use(Actor *);
  void Wear(Actor *);

  virtual std::stringstream * Save(Saver *);
  std::stringstream * Save(Saver *, int);
};

#endif
