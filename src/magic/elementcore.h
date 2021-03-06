#ifndef ELEMENTCORE_H
#define ELEMENTCORE_H

#include <glm/glm.hpp>
#include <magic/protocore.h>

class ElementMagicCore : public ProtoMagicCore {
  virtual ProtoMagicCore * CreateElement(glm::vec3);
 public:
  ElementMagicCore();
  char CallCreateElement(char, AbstractCore *);
  char Call(char, char, AbstractCore *);
};

#endif
