#include <magic/elementpiece.h>

ElementPiece::ElementPiece(Mesh* mesh, bool isActive, bool isVisible, bool isTransparent, bool isFlying, glm::vec3 position, glm::vec3 rotation, std::string name) :
  PhysicalObj(mesh, isActive, isVisible, isTransparent, isFlying, position, rotation, name, new BoundaryBox(0.5f, 0.5f, 0.5f)) {
}


void ElementPiece::update(float dt) {
  PhysicalObj::update(dt);
  this->changeRotation(glm::vec3(1.0f, 1.0f, 1.0f));
}
