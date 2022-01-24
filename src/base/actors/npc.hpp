/**
 * \file
 * \brief This file contains declaration of NPC
 */
#ifndef NPC_H
#define NPC_H

#include "actor.hpp"
#include "npcai/npcai.hpp"
#include "dialog.hpp"

/**
 * \brief NPC represents non-playable character (Characters created to interact with player, making the game more 'live')
 */
class NPC : public Actor {
protected:
  NPCAI * ai;
    Dialog * dialog;
 public:
  NPC();
  NPC(std::string, int, PhysicalObj *);
  NPC(std::string, int, PhysicalObj *, NPCAI *);

  NPCAI * GetAI();
  void Process(float dt);
    Dialog * getDialog();
};

#endif
