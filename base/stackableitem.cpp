#include "stackableitem.h"
#include "entries.h"

int StackableItem::GetCount() {
  return this->count;
}

void StackableItem::SetCount(int count) {
  this->count = count;
}

void StackableItem::Use(Actor * target) {
  this->count--;
  if(this->count == 0) {
     target->DeleteItem(this);
  }
}

bool StackableItem::IsStackable() {
  return true;
}

void StackableItem::Stack(StackableItem * item) {
  this->SetCount(this->GetCount() + item->GetCount());
  item->SetCount(0);
}

std::stringstream * StackableItem::Save(Saver * saver, int entry) {
  std::stringstream * ss = Item::Save(saver, entry);
  saver->SaveInt(ss, this->count);

  return ss;
}

std::stringstream * StackableItem::Save(Saver * saver) {
  return this->Save(saver, ENTRY_STACKABLE);
}
