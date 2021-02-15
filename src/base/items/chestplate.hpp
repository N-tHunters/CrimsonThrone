/**
 * \file
 * \brief This file contains declaration of Chestplate
 */
#ifndef CHESTPLATE_H
#define CHESTPLATE_H

#include <base/items/armor.hpp>
#include <base/saver.hpp>
#include <sstream>

class Actor;

/**
 * \brief Chestplate is a piece of Armor worn on chest.
 *
 * All functions are implemented from Armor, except Chestplate::Wear() and slightly modified Chestplate::Save(Saver *)
 */
class Chestplate : public Armor {
public:
  Chestplate(std::string, PhysicalObj *, int);
  Chestplate(std::string, int);
  void Wear(Actor *);

  std::stringstream * Save(Saver *);
};

#endif
