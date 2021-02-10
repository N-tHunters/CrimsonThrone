#include <magic/elementpiece.h>

ElementPiece::ElementPiece(Mesh* mesh, bool isActive, bool isVisible, bool isTransparent, bool isFlying, glm::vec3 position, glm::vec3 rotation, std::string name) :
  PhysicalObj(mesh, isActive, isVisible, isTransparent, isFlying, position, rotation, name) {
}


void ElementPiece::update(float dt) {
  PhysicalObj::update(dt);
  this->changeRotation(glm::vec3(10.0f, 10.0f, 10.0f));
}
