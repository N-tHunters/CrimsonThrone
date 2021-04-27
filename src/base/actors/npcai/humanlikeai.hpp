#pragma once

#include <base/actors/npcai/wanderai.hpp>

#define SATISFY_HUNGER 1

class HumanlikeAI : public WanderAI {
protected:
  double hunger;
  double fatigue;
  double social_dissatisfaction;
  double individuality;

  double hunger_threshold;
  double gluttony_priority_modifier;

  double greed_modifier;

  unsigned int flags;

  double work_intensity;
  
public:
  HumanlikeAI();

  unsigned int GetFlags();
  void SetFlags();
  
  void SetFlag(int flag);
  void UnsetFlag(int flag);
  virtual void Process(float dt);

  void SetActor(Actor *);
};
