#ifndef STACKABLEITEM_H
#define STACKABLEITEM_H

#include "item.h"
#include "actor.h"
#include "saver.h"
#include <sstream>

class StackableItem : public Item {
 private:
  int count;
 public:
  int GetCount();
  void SetCount(int);
  bool IsStackable();
  void Use(Actor *);
  void Stack(StackableItem *);

  std::stringstream Save(Saver *);
  std::stringstream Save(Saver *, int);
};

#endif
