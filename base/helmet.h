/**
 * \file
 * \brief This file contains declaration of Helmet
 */
#ifndef HELMET_H
#define HELMET_H

#include "armor.h"
#include "saver.h"
#include "../physics/physicalObj.h"
#include <string>
#include <sstream>

class Actor;

/**
 * \brief Helmet is a piece of Armor worn on head
 */
class Helmet : public Armor {
public:
  Helmet(std::string, PhysicalObj *, int);
  Helmet(std::string, int);
  void Wear(Actor *);

  std::stringstream * Save(Saver *);
};

#endif
