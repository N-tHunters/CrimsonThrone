#include "objectcontrolcore.h"

ObjectControlCore::ObjectControlCore(PhysicalObj * obj) : ProtoMagicCore(obj) {
  
}

char ObjectControlCore::SetVelocity(char arg, AbstractCore * core) {
  this->GetPhysicalObj()->setSpeed(glm::vec3(1.0f, 10.0f, 1.0f));
  return 0;
}

char ObjectControlCore::Call(char id, char arg, AbstractCore * core) {
  switch(id) {
    
  case 0:
    return this->SetVelocity(arg, core);
  }
  return 0;
}
