#include "missle.h"
#include "entries.h"

std::stringstream Missle::Save(Saver* saver) {
  return StackableItem::Save(saver, ENTRY_MISSLE);
}
