#include "healpotion.h"
#include "stackableitem.h"
#include "actor.h"
#include "entries.h"

int HealPotion::GetHealAmount() {
  return this->heal_amount;
}

void HealPotion::SetHealAmount(int heal_amount) {
  this->heal_amount = heal_amount;
}

void HealPotion::Use(Actor * target) {
  target->Heal(this->GetHealAmount());
  StackableItem::Use(target);
}

bool HealPotion::IsUsable() {
  return true;
}

std::stringstream HealPotion::Save(Saver * saver) {
  std::stringstream ss = StackableItem::Save(saver, ENTRY_HEALPOTION);
  saver->SaveInt(&ss, this->heal_amount);
  return ss;
}
