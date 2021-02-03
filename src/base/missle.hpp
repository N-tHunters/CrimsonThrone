/**
 * \file
 * \brief This file contains declaraion of Missle
 */
#ifndef MISSLE_H
#define MISSLE_H

#include "stackableitem.hpp"
#include "saver.hpp"

class Missle : public StackableItem {
public:
  std::stringstream * Save(Saver *);
};

#endif
