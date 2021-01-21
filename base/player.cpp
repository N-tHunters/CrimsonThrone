/**
 * \file
 * \brief This file contains implementation of Player
 */
#include "player.hpp"

/**
 * Empty constructor - calls Actor::Actor()
 * \warning Should not use!
 */
Player::Player() : Actor() {}

/**
 * Default constructor
 * \param name Name
 * \param max_health Maximum health
 * \param obj Physical object
 * \param camera View camera
 */
Player::Player(std::string name, int max_health, PhysicalObj * obj, Camera * camera) :
  Actor(name, max_health, obj)
{
  this->camera = camera;
}

/**
 * Update physics for player and position for camera
 * \param dt Time passed since last update
 */
void Player::Update(float dt) {
  this->GetPhysicalObj()->update(dt);
  this->camera->setPosition(this->GetPhysicalObj()->getPosition());
}

/**
 * Get pointer to player camera
 * \return Pointer to camera
 */
Camera * Player::GetCamera() {
  return this->camera;
}

/**
 * Set camera for player
 * \param camera Pointer to new camera
 */
void Player::SetCamera(Camera * camera) {
  this->camera = camera;
}
