/**
 * \file
 * \brief This file contains declaration of StackableItem
 */
#ifndef STACKABLEITEM_H
#define STACKABLEITEM_H

#include "item.h"
#include "actor.h"
#include "saver.h"
#include <sstream>

/**
 * \brief StackableItem is an Item, that can be stacked with others and have amount.
 *
 * Mainly used for one-time items, like Missle or HealPotion
 */
class StackableItem : public Item {
 private:
  int count;
 public:
  int GetCount();
  void SetCount(int);
  bool IsStackable();
  void Use(Actor *);
  void Stack(StackableItem *);

  std::stringstream * Save(Saver *);
  std::stringstream * Save(Saver *, int);
};

#endif
