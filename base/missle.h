/**
 * \file
 * \brief This file contains declaraion of Missle
 */
#ifndef MISSLE_H
#define MISSLE_H

#include "stackableitem.h"
#include "saver.h"

class Missle : public StackableItem {
public:
  std::stringstream * Save(Saver *);
};

#endif
