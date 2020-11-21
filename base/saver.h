/**
 * \file
 * \brief This file contains declaration of Saver
 */
#ifndef SAVER_H
#define SAVER_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

class Actor;
class Item;

/**
 * \brief Saver serves as serializer for objects and saves binary representation of game objects to file
 */
class Saver {
  std::string path;
  std::vector<Actor*>*actors;
  std::vector<Item*>*items;
  std::map<Item*, int>item2index;
 public:
  Saver(std::string, std::vector<Actor*>*, std::vector<Item*>*);
  
  void SaveInt(std::stringstream *, int);
  void SaveInt(std::ofstream *, int);
  void SaveString(std::stringstream *, std::string);
  void SaveString(std::ofstream *, std::string);

  void SaveItem(std::stringstream *, Item *);

  void Save();
};

#endif
