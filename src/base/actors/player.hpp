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
  Camera * m_camera;
  glm::vec2 m_speed;
  glm::vec2 m_side_speed;
public:
  Player();
  Player(std::string, int, PhysicalObj *, Camera *);

  void Update(float);

  void SetCamera(Camera *);
  Camera * GetCamera();

  void SetSpeed(glm::vec2 speed);
  void SetSideSpeed(glm::vec2 side_speed);

  glm::vec2 GetSpeed();
  glm::vec2 GetSideSpeed();

  void CalculateSpeed(float rotation, float velocity, float direction);
  void CalculateSideSpeed(float rotation, float velocity, float direction);

  void draw(ShaderHolder*, Camera*, int, int);
};

#endif
