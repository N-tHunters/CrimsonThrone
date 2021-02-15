/**
 * \file
 * \brief This file contains declaration of RangedWeapon
 */
#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include <base/items/weapon.hpp>
#include <base/items/missle.hpp>
#include <base/actors/actor.hpp>
#include <sstream>

/**
 * \brief RangeWeapon is a Weapon that uses Missle to shoot and deal damage
 */
class RangedWeapon : public Weapon {
 private:
  Missle *missle;
    
 public:
  Missle *GetMissle();
  void SetMissle(Missle *);
  void UseMissle(Actor *);

  std::stringstream * Save(Saver *);
};

#endif

  
