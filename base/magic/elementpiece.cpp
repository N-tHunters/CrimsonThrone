#include "elementpiece.h"

ElementPiece::ElementPiece(Mesh* mesh, bool isActive, bool isVisible, bool isTransparent, glm::vec3 position, glm::vec3 rotation, std::string name) :
  PhysicalObj(mesh, isActive, isVisible, isTransparent, position, rotation, name) {

}


void ElementPiece::update(float dt) {
  PhysicalObj::update(dt);
  this->changeRotation(glm::vec3(1.0f, 1.0f, 1.0f));
}
