/**
 * \file
 * \brief This file contains declaration of HealPotion
 */
#ifndef HEALPOTION_H
#define HEALPOTION_H

#include "stackableitem.h"
#include "actor.h"
#include "saver.h"
#include <sstream>

/**
 * \brief HealPotion is an Item that is used to heal (increase amount of current health) Actors.
 */
class HealPotion : public StackableItem {
 private:
  int heal_amount;
 public:
  int GetHealAmount();
  void SetHealAmount(int);

  void Use(Actor *);

  bool IsUsable();

  std::stringstream * Save(Saver *);
};
#endif
