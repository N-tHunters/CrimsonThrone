#ifndef FIRECORE_H
#define FIRECORE_H

#include "elementcore.h"

class FireMagicCore : public ElementMagicCore {
  ProtoMagicCore * CreateElement(glm::vec3);
 public:
  FireMagicCore();
};


#endif
