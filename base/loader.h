/**
 * \file
 * \brief This file contains declaration of Loader
 */
#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include "actor.h"
#include "item.h"

/**
 * \brief Loader is an abstract class used to load binary saves
 */
class Loader {
private:
  std::string path;
  std::vector<Item*>*items;
  std::vector<Actor*>*actors;
  std::map<int, Item*> index2item;

public:
  Loader(std::string, std::vector<Actor*>*, std::vector<Item*>*);
  int LoadInt(std::ifstream *);
  int LoadInt(std::stringstream*);
  std::string LoadString(std::ifstream *);
  std::string LoadString(std::stringstream*);

  Item * LoadItem(std::ifstream *, int);
  
  void Load();
};

#endif
