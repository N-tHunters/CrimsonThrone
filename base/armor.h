/**
 * \file
 * \brief This file contains declaration of Armor
 */
#ifndef ARMOR_H
#define ARMOR_H

#include "item.h"
#include "saver.h"
#include "../physics/physicalObj.h"
#include <sstream>
#include <string>

/**
 * Armor is an Item used to raise Actor's defence
 */
class Armor : public Item {
 private:
  int defence;

 public:
  Armor(std::string, PhysicalObj *, int);
  Armor(std::string, int);
  Armor();
  int GetDefence();

  void SetDefence(int);

  bool IsWearable();

  virtual std::stringstream * Save(Saver *, int);
  virtual std::stringstream * Save(Saver *);
};

#endif
