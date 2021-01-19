/**
 * \file
 * \brief This file contains implementation of HealPotion
 */
#include "healpotion.hpp"
#include "stackableitem.hpp"
#include "actor.hpp"
#include "entries.hpp"

/**
 * Get amount of health points healed by this potion
 * \return Amount of health points healed
 */
int HealPotion::GetHealAmount() {
  return this->heal_amount;
}

/**
 * Set amount of health points healed by this potion
 * \param heal_amount New amount of heal
 */
void HealPotion::SetHealAmount(int heal_amount) {
  this->heal_amount = heal_amount;
}

/**
 * Use this potion on actor
 * \param target Who is using this potion
 */
void HealPotion::Use(Actor * target) {
  target->Heal(this->GetHealAmount());
  StackableItem::Use(target);
}

/**
 * Is this item usable?
 * Potions are usable, so always true
 * \return Always true
 */
bool HealPotion::IsUsable() {
  return true;
}

/**
 * Convert object to binary stream.
 * \param saver Serializer
 * \return Binary stream represnting this object
 */
std::stringstream * HealPotion::Save(Saver * saver) {
  std::stringstream * ss = StackableItem::Save(saver, ENTRY_HEALPOTION);
  saver->SaveInt(ss, this->heal_amount);
  return ss;
}
