/**
 * \file
 * \brief This file contains declaration of Player
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "actor.hpp"
#include <render/camera.hpp>

/**
 * \brief Human controlled game character
 *
 * Player is a human controlled game character. It uses camera to render his point of view and acts like any other character in other ways.
 */
class Player : public Actor {
private:
  Camera * camera;
public:
  Player();
  Player(std::string, int, PhysicalObj *, Camera *);

  void Update(float);

  void SetCamera(Camera *);
  Camera * GetCamera();
};

#endif
