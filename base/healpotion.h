#ifndef HEALPOTION_H
#define HEALPOTION_H

#include "stackableitem.h"
#include "actor.h"
#include "saver.h"
#include <sstream>

class HealPotion : public StackableItem {
 private:
  int heal_amount;
 public:
  int GetHealAmount();
  void SetHealAmount(int);

  void Use(Actor *);

  bool IsUsable();

  std::stringstream Save(Saver *);
};
#endif
