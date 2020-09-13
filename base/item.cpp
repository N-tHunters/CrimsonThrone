#include <string>

#include "item.h"
#include "actor.h"
#include "saver.h"
#include "entries.h"



Item::Item(std::string name) {
  this->name = name;
}

Item::Item() {}

std::string Item::GetName() {
  return this->name;
}

void Item::SetName(std::string name) {
  this->name = name;
}

bool Item::IsWearable() {
  return false;
}

bool Item::IsUsable() {
  return false;
}

bool Item::IsStackable() {
  return false;
}

void Item::Use(Actor *) {}
void Item::Wear(Actor *) {}


std::stringstream Item::Save(Saver * saver) {
  return this->Save(saver, ENTRY_ITEM);
}

std::stringstream Item::Save(Saver * saver, int entry) {
  std::stringstream ss;
  
  saver->SaveInt(&ss, entry);
  saver->SaveString(&ss, this->name);
  
  return ss;
}
