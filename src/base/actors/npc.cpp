/**
 * \file
 * \brief This file contains implementation of NPC
 */
#include "npc.hpp"
#include "npcai/npcai.hpp"
#include "dialog.hpp"

/**
 * Empty constructor
 * \warning Should not use
 */
NPC::NPC() {
  this->ai = nullptr;
  this->dialog = new Dialog();
}

/**
 * Default constructor - just the same as the Actor::Actor(std::string, int, PhysicalObj *)
 * \param name Name
 * \param max_health Maximum health
 * \param obj Physical representation
 */
NPC::NPC(std::string name, int max_health, PhysicalObj * obj) :
  NPC(name, max_health, obj, new NPCAI()) {}

/**
 * Constructs new instance of NPC with given attributes (NPCAI included). Use this for constructing fully-functional NPC's
 * \param name Name
 * \param max_health Maximum health
 * \param obj Physical representation
 * \param ai Controller of the NPC
 */
NPC::NPC(std::string name, int max_health, PhysicalObj * obj, NPCAI * ai) :
  Actor(name, max_health, obj) {
  this->ai = ai;
  this->ai->SetActor(this);
}

NPCAI* NPC::GetAI() {
  return ai;
}

void NPC::Process(float dt) {
  if(this->ai != nullptr) 
    this->ai->Process(dt);
}


Dialog * getDialog() {
  return this->dialog;
}
