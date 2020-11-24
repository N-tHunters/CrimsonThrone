/**
 * \file
 * \brief This file contains implementation of StackableItem
 */
#include "stackableitem.h"
#include "entries.h"

/**
 * Get amount of this item
 * \return Amount of items
 */
int StackableItem::GetCount() {
  return this->count;
}

/**
 * Set amount of this item
 * \param count New amount
 */
void StackableItem::SetCount(int count) {
  this->count = count;
}

/**
 * Use this item. Makes amount of items to decrease
 * \param target Actor that uses this item
 */
void StackableItem::Use(Actor * target) {
  this->count--;
  if(this->count == 0) {
     target->DeleteItem(this);
  }
}

/**
 * Is this item stackable? Of course, it's StackableItem!
 * \return true
 */
bool StackableItem::IsStackable() {
  return true;
}

/**
 * Stack this item with other (with the same type, I hope)
 * \warning No checks for type of other item. Just change amount. Use carefully!
 * \param item Item to stack with
 */
void StackableItem::Stack(StackableItem * item) {
  this->SetCount(this->GetCount() + item->GetCount());
  item->SetCount(0);
}

/**
 * Convert object to binary stream.
 * \param saver Serializer object
 * \param entry Identificator of binary representation
 * \return Binary representation as stream
 */
std::stringstream * StackableItem::Save(Saver * saver, int entry) {
  std::stringstream * ss = Item::Save(saver, entry);
  saver->SaveInt(ss, this->count);

  return ss;
}

/**
 * Convert object to binary stream and use default identifier.
 * \param saver Serializer object
 * \return Binary representation of object
 */
std::stringstream * StackableItem::Save(Saver * saver) {
  return this->Save(saver, ENTRY_STACKABLE);
}
