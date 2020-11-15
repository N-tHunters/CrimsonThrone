#include "elementcore.h"

ElementMagicCore::ElementMagicCore() {}

ProtoMagicCore * ElementMagicCore::CreateElement(glm::vec3) {
  return nullptr;
}

char ElementMagicCore::CallCreateElement(char arg, AbstractCore * core) {
  switch(arg) {
  case 0:
    PhysicalObj * core_obj = core->GetPhysicalObj();
    ProtoMagicCore * element_core = this->CreateElement(core_obj->getPosition());
    return core->AddChildProtoCore(element_core);
  }

  return 0;
}

char ElementMagicCore::Call(char id, char arg, AbstractCore * core) {
  switch(id) {
  case 0:
    return this->CallCreateElement(arg, core);
  }
  return 0;
}
