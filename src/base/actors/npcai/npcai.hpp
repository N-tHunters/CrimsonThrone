#pragma once

#include <base/actors/actor.hpp>

class NPCAI {
protected:
  Actor * actor;
public:
  NPCAI();

  void SetActor(Actor *);
  
  virtual void Process();
  virtual void Communicate(Actor *);
};
