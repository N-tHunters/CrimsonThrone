#include "elementpiece.h"

ElementPiece::ElementPiece(Mesh* mesh, bool isActive, bool isVisible, bool isTransparent, glm::vec3 position, glm::vec3 rotation, std::string name) :
  PhysicalObj(mesh, isActive, isVisible, isTransparent, position, rotation, name) {

}
