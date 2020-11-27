#include "objectcontrolcore.h"

ObjectControlCore::ObjectControlCore(PhysicalObj * obj) : ProtoMagicCore(obj) {
  
}

char ObjectControlCore::SetVelocity(char arg, AbstractCore * core) {
  this->GetPhysicalObj()->jump();
  return 0;
}

char ObjectControlCore::Call(char id, char arg, AbstractCore * core) {
  switch(id) {
    
  case 0:
    return this->SetVelocity(arg, core);
  }
  return 0;
}
