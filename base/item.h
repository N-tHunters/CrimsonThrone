#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <sstream>

class Actor;
class Saver;

class Item {
private:
  std::string name;

  std::string LogDescribe();

public:
  Item(std::string);
  Item();
  
  std::string GetName();
  void SetName(std::string);

  virtual bool IsUsable();
  virtual bool IsWearable();
  virtual bool IsStackable();

  virtual void Wear(Actor *);
  virtual void Use(Actor *);

  virtual std::stringstream Save(Saver *);
  virtual std::stringstream Save(Saver *, int);
};

#endif
  
