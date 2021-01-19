/**
 * \file
 * \brief This file contains declaration of Boots
 */
#ifndef BOOTS_H
#define BOOTS_H

#include "armor.hpp"
#include "saver.hpp"
#include <sstream>

class Actor;

/**
 * \brief Boots are pieces of Armor worn on feet.
 *
 * All functions are implemented from Armor, except Boots::Wear() and slightly modified Boots::Save(Saver *)
 */
class Boots : public Armor {
public:
  Boots(std::string, PhysicalObj *, int);
  Boots(std::string, int);
  void Wear(Actor *);

  std::stringstream * Save(Saver *);
};

#endif
