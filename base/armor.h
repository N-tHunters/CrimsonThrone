#ifndef ARMOR_H
#define ARMOR_H

#include "item.h"
#include "saver.h"
#include <sstream>
#include <string>

class Armor : public Item {
 private:
  int defence;

 public:
  Armor(std::string, int);
  int GetDefence();

  void SetDefence(int);

  bool IsWearable();

  virtual std::stringstream Save(Saver *, int);
  virtual std::stringstream Save(Saver *);
};

#endif
