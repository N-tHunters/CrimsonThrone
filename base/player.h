#ifndef PLAYER_H
#define PLAYER_H

#include "actor.h"
#include "../render/camera.h"

class Player : public Actor {
private:
  Camera * camera;
public:
  Player();
  Player(std::string, int, PhysicalObj *, Camera *);

  void Update();

  void SetCamera(Camera *);
  Camera * GetCamera();
};

#endif
