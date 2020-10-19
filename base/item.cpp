#include <string>

#include "item.h"
#include "actor.h"
#include "saver.h"
#include "entries.h"



Item::Item(std::string name, PhysicalObj * obj) {
  this->name = name;
  this->obj = obj;
}

Item::Item(std::string name) :
  Item(name, new PhysicalObj()) {};

Item::Item() {}

std::string Item::GetName() {
  return this->name;
}

PhysicalObj* Item::GetPhysicalObj() {
  return this->obj;
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


std::stringstream * Item::Save(Saver * saver) {
  return this->Save(saver, ENTRY_ITEM);
}

std::stringstream * Item::Save(Saver * saver, int entry) {
  std::stringstream * ss = new std::stringstream();
  
  saver->SaveInt(ss, entry);
  saver->SaveString(ss, this->name);
  
  return ss;
}

std::vector<std::string *> * Item::Describe() {
  std::vector<std::string *> * description;
  description->push_back(new std::string("Item"));
  description->push_back(&this->name);
  return description;
}
