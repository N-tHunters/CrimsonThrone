#ifndef ELEMENTPIECE_H
#define ELEMENTPIECE_H

#include <physics/physicalObj.hpp>

class ElementPiece : public PhysicalObj {
 public:
  ElementPiece(Mesh*, bool, bool, bool, bool, glm::vec3, glm::vec3, std::string);
  void update(float dt);
};

#endif
