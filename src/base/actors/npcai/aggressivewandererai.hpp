#pragma once

#include <base/actors/npcai/wanderai.hpp>

class AggressiveWandererAI : public WanderAI {
protected:
  PhysicalObj *target;
public:
  AggressiveWandererAI(float speed);
  virtual void Process(float dt);
  virtual bool GoToTarget();
  virtual void ProcessHit(Actor *);
  void SetTarget(PhysicalObj *);
};
