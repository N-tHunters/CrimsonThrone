
/**
 * \file
 * \brief This file contains declaration of NPC
 */
#ifndef NPC_H
#define NPC_H

#include "actor.h"

/**
 * \brief NPC represents non-playable character (Characters created to interact with player, making the game more 'live')
 */
class NPC : public Actor {
 private:
 public:
  NPC();
  NPC(std::string, int, PhysicalObj *);
};

#endif
