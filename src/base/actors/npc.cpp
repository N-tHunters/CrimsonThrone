/**
 * \file
 * \brief This file contains implementation of NPC
 */
#include "npc.hpp"

/**
 * Empty constructor
 * \warning Should not use
 */
NPC::NPC() {}

/**
 * Default constructor - just the same as the Actor::Actor(std::string, int, PhysicalObj *)
 * \param name Name
 * \param max_health Maximum health
 * \param obj Physical representation
 */
NPC::NPC(std::string name, int max_health, PhysicalObj * obj) :
  Actor(name, max_health, obj) {}
