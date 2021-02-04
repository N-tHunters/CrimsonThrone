/**
 * \file
 * \brief This file contains declaration of Leggins
 */
#ifndef LEGGINS_H
#define LEGGINS_H

#include "armor.hpp"
#include "saver.hpp"
#include <sstream>

class Actor;

/**
 * \brief Leggins are piece of Armor worn on legs
 */
class Leggins : public Armor {
public:
  Leggins(std::string, PhysicalObj *, int);
  Leggins(std::string, int);
  void Wear(Actor *);

  std::stringstream * Save(Saver *);
};

#endif
