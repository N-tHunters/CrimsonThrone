/**
 * \file
 * \brief This file contains declaraion of Missle
 */
#ifndef MISSLE_H
#define MISSLE_H

#include <base/items/stackableitem.hpp>
#include <base/saver.hpp>

class Missle : public StackableItem {
public:
  std::stringstream * Save(Saver *);
};

#endif
