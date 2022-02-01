#pragma once

#include <base/actors/actor.hpp>

class NPCAI {
protected:
  Actor * actor;
public:
  NPCAI();

  virtual void SetActor(Actor *);
  
  virtual void Process(float dt);
  virtual void ProcessHit(Actor *);
  virtual void Communicate(Actor *);
};
