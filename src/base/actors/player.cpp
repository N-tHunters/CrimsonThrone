/**
 * \file
 * \brief This file contains implementation of Player
 */
#include "player.hpp"
#include <base/items/weapon.hpp>

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
  m_camera = camera;
}

/**
 * Update physics for player and position for camera
 * \param dt Time passed since last update
 */
void Player::Update(float dt) {
  this->GetPhysicalObj()->update(dt);
  m_camera->setPosition(this->GetPhysicalObj()->getPosition() + glm::vec3(0.0f, 1.0f, 0.0f));
}

/**
 * Get pointer to player camera
 * \return Pointer to camera
 */
Camera * Player::GetCamera() {
  return m_camera;
}

/**
 * Set camera for player
 * \param camera Pointer to new camera
 */
void Player::SetCamera(Camera * camera) {
  m_camera = camera;
}

glm::vec2 Player::GetSpeed() {
  return m_speed;
}

glm::vec2 Player::GetSideSpeed() {
  return m_side_speed;
}

void Player::SetSpeed(glm::vec2 speed) {
  m_speed = speed;
}

void Player::SetSideSpeed(glm::vec2 side_speed) {
  m_side_speed = side_speed;
}

void Player::CalculateSpeed(float rotation, float velocity, float direction) {
  SetSpeed(glm::vec2(sin(glm::radians(rotation)), -cos(glm::radians(rotation))) * velocity * direction);
}

void Player::CalculateSideSpeed(float rotation, float velocity, float direction) {
  SetSpeed(glm::vec2(cos(glm::radians(rotation)), -sin(glm::radians(rotation))) * velocity * direction);
}

void Player::draw(ShaderHolder* shaderHolder, Camera* camera, int width, int height) {
  if(this->weapon != nullptr) {
    glm::mat4 rotation_matrix = glm::mat4(1.0f);
    rotation_matrix = glm::rotate(rotation_matrix, glm::radians(this->m_camera->getRotationY() - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec4 offset_vec4 = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f) * rotation_matrix;
    glm::vec3 offset = glm::vec3(offset_vec4);
    this->weapon->GetPhysicalObj()->setPosition(this->obj->getPosition() + offset);
    this->weapon->GetPhysicalObj()->setRotation(glm::vec3(0.0f, -this->m_camera->getRotationY() + 90.0f, 135.0f));
    this->weapon->GetPhysicalObj()->draw(shaderHolder, camera, width, height);
  }
}