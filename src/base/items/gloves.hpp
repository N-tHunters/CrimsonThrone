/**
 * \file
 * \brief This file contains declaration of Gloves
 */
#ifndef GLOVES_H
#define GLOVES_H

#include <base/items/armor.hpp>
#include <base/saver.hpp>
#include <sstream>

class Gloves;

/**
 * \brief Gloves are piece of Armor worn on hands
 */
class Gloves : public Armor {
public:
  Gloves(std::string, PhysicalObj *, int);
  Gloves(std::string, int);
  void Wear(Actor *);

  std::stringstream * Save(Saver *);
};

#endif
