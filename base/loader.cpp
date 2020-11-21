/**
 * \file
 * \brief This file contains implementation of Loader
 */
#include "loader.h"
#include "weapon.h"
#include "armor.h"
#include "helmet.h"
#include "chestplate.h"
#include "entries.h"
#include "gloves.h"
#include "leggins.h"
#include "boots.h"

/**
 * Basic constructor
 * \param path Path to save file to load
 * \param[out] actors Pointer to vector where to load
 * \param[out] items Pointer to vector where to load
 */
Loader::Loader(std::string path, std::vector<Actor *>* actors, std::vector<Item *>* items) {
  this->path = path;
  this->actors = actors;
  this->items = items;
}

/**
 * Load integer from binary stream (std::ifstream)
 * \param ss Pointer to stream where to load from
 * \return Parsed int
 */
int Loader::LoadInt(std::ifstream *ss) {
  int value;
  ss->read((char *)&value, sizeof(int));
  return value;
}

/**
 * Load int from binary stream (std::stringstream)
 * \param ss Pointer to stream to load from
 * \return Parsed int
 */
int Loader::LoadInt(std::stringstream* ss) {
  int value;
  ss->read((char *)&value, sizeof(int));
  return value;
}

/**
 * Load string from binary stream (std::ifstream)
 * \param ss Pointer to stream to load from
 * \return Parsed string
 */
std::string Loader::LoadString(std::ifstream *ss) {
  int length = this->LoadInt(ss);
  char cstr[256];

  ss->read(cstr, length);
  cstr[length] = 0;

  return std::string(cstr);
}

/**
 * Load string from binary stream (std::stringstream)
 * \param ss Pointer to stream to load from
 * \return Parsed string
 */
std::string Loader::LoadString(std::stringstream* ss) {
  int length = this->LoadInt(ss);
  char cstr[256];

  ss->read(cstr, length);
  cstr[length] = 0;

  return std::string(cstr);
}

/**
 * Load Item from binary stream (std::ifstream)
 * \param ss Pointer to stream to load from
 * \param entry_size Size of binary representation of object (embedded into header)
 * \return Parsed item
 */
Item * Loader::LoadItem(std::ifstream *ss, int entry_size) {
  const int entry_type = this->LoadInt(ss);

  std::string item_name = this->LoadString(ss);
  int item_damage;
  int item_range;
  int item_defence;

  printf("Entry tag is %d and name is %s\n", entry_type, item_name.c_str());

  switch(entry_type) {
  case ENTRY_ITEM:
    return new Item(item_name);

  case ENTRY_WEAPON:
    item_damage = this->LoadInt(ss);
    item_range = this->LoadInt(ss);

    return new Weapon(item_name, item_damage, item_range);

  case ENTRY_ARMOR:
    item_defence = this->LoadInt(ss);

    return new Armor(item_name, item_defence);

  case ENTRY_HELMET:
    item_defence = this->LoadInt(ss);

    return new Helmet(item_name, item_defence);

  case ENTRY_CHESTPLATE:
    item_defence = this->LoadInt(ss);

    return new Chestplate(item_name, item_defence);

  case ENTRY_GLOVES:
    item_defence = this->LoadInt(ss);

    return new Gloves(item_name, item_defence);

  case ENTRY_LEGGINS:
    item_defence = this->LoadInt(ss);

    return new Leggins(item_name, item_defence);

  case ENTRY_BOOTS:
    item_defence = this->LoadInt(ss);

    return new Boots(item_name, item_defence);
  }
  
  return nullptr;
}

/**
 * Load entire file
 * \todo Finish actor loading
 * \todo Finish loading of nested items
 */
void Loader::Load() {
  std::ifstream stream(this->path, std::ifstream::binary);

  // Load header information
  int items_count = this->LoadInt(&stream);
  int actors_count = this->LoadInt(&stream);

  printf("Loading %d items and %d actors...\n", items_count, actors_count);

  // Load items

  for(int i = 0; i < items_count; i ++) {
    int entry_size = this->LoadInt(&stream);

    this->items->push_back(this->LoadItem(&stream, entry_size));
  }

  // Update item handlers for items
  /*
  for(int i = 0; i < items_count; i++) {
    this->PostLoad(this->items[i]);
  }
  */

  // Load actors

  for(int i = 0; i < actors_count; i ++);

  stream.close();
}
