#ifndef VOIDCORE_H
#define VOIDCORE_H

#include "elementcore.h"

const char CORE_ID_VOID = 8;

class VoidMagicCore : public ElementMagicCore {
  ProtoMagicCore * CreateElement(glm::vec3);
 public:
  VoidMagicCore();
};

#endif
