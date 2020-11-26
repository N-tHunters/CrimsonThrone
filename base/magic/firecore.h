#ifndef FIRECORE_H
#define FIRECORE_H

#include "elementcore.h"

const char CORE_ID_FIRE = 1;

class FireMagicCore : public ElementMagicCore {
  ProtoMagicCore * CreateElement(glm::vec3);
 public:
  FireMagicCore();
};


#endif
