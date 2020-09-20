#include "saver.h"
#include "actor.h"
#include "item.h"
#include <stdio.h>


Saver::Saver(std::string path, std::vector<Actor*>* actors, std::vector<Item*>* items) {
  this->actors = actors;
  this->items = items;

  this->path = path;
}

void Saver::SaveInt(std::stringstream *ss, int value) {
  ss->write((const char *)&value, sizeof(int));
  (*ss) << std::flush;
}

void Saver::SaveInt(std::ofstream *ss, int value) {
  ss->write((const char *)&value, sizeof(int));
  (*ss) << std::flush;
}

void Saver::SaveString(std::ofstream *ss, std::string str) {
  int size = str.size();
  ss->write((const char *)&size, sizeof(int));
  ss->write(str.c_str(), size);
}

void Saver::SaveString(std::stringstream * ss, std::string str) {
  int size = str.size();
  ss->write((const char *)&size, sizeof(int));
  ss->write(str.c_str(), size);
}

void Saver::SaveItem(std::stringstream * ss, Item * item) {
  if (item == nullptr)
    this->SaveInt(ss, -1);
  else
    this->SaveInt(ss, this->item2index[item]);
}

void Saver::Save() {
  // Initialize and prepare
  std::ofstream fs;
  fs.open(this->path.c_str(), std::ofstream::binary | std::ofstream::trunc);

  this->item2index.clear();

  // Save items

  this->SaveInt(&fs, (int)this->items->size());
  this->SaveInt(&fs, (int)this->actors->size());
  
  for(unsigned int i = 0; i < this->items->size(); i++)
    this->item2index[(*this->items).at(i)] = i;
  
  for(unsigned int i = 0; i < this->items->size(); i++) {
    std::stringstream item_ss = this->items->at(i)->Save(this);

    item_ss.seekg(0, std::ios::end);
    this->SaveInt(&fs, item_ss.tellg());
    item_ss.seekg(0, std::ios::beg);
    
    fs << item_ss.rdbuf();
  }

  for(unsigned int i = 0; i < this->actors->size(); i++) {
    std::stringstream actor_ss = this->actors->at(i)->Save(this);

    actor_ss.seekg(0, std::ios::end);
    this->SaveInt(&fs, actor_ss.tellg());
    actor_ss.seekg(0, std::ios::beg);

    fs << actor_ss.rdbuf();
  }
  
  fs.close();
}
