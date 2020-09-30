#include "player.h"

Player::Player() : Actor() {}

Player::Player(std::string name, int max_health, PhysicalObj obj, Camera * camera) :
  Actor(name, max_health, obj)
{
  this->camera = camera;
}


void Player::Update() {
  this->camera->setPosition(this->GetPhysicalObj()->getPosition());
}
