#pragma once

#include <string>
#include <map>


class ItemDB {
  std::map<std::string, Item*> items;
public:
  ItemDB(std::string path);
  void loadItems();
  
  unsigned int size();

  void addItem(Item*);
  
};
