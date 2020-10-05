#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "weapon.h"
#include "missle.h"
#include "actor.h"
#include <sstream>

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

  
