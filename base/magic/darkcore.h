#ifndef DARKCORE_H
#define DARKCORE_H

#include "elementcore.h"

const char CORE_ID_DARK = 7;

class DarkMagicCore : public ElementMagicCore {
  ProtoMagicCore * CreateElement(glm::vec3);
 public:
  DarkMagicCore();
};

#endif
