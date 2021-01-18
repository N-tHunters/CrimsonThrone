#include "elementcore.h"

ElementMagicCore::ElementMagicCore() {}

ProtoMagicCore * ElementMagicCore::CreateElement(glm::vec3) {
  return nullptr;
}

char ElementMagicCore::CallCreateElement(char arg, AbstractCore * core) {
  switch(arg) {
  case 0:
    PhysicalObj * core_obj = core->GetPhysicalObj();
    glm::vec3 position(0.0f, 0.0f, 0.0f);
    if(core_obj != nullptr)
      position = core_obj->getPosition();
    ProtoMagicCore * element_core = this->CreateElement(position);
    return core->AddChildProtoCore(element_core);
  }

  if(1 <= arg && arg <= 125) {
    int x = (arg - 1) / 25;
    int y = ((arg - 1) % 25) / 5;
    int z = ((arg - 1) % 25) % 5;

    PhysicalObj * core_obj = core->GetPhysicalObj();

    // Get position? Convert pseudo x y z to normal and rotate around caller
    glm::vec3 position(x * 0.5f, 2.5f - 0.5f * y, 0.5f * z);
    if(core_obj != nullptr) {
      position += core_obj->getPosition();

    }
    ProtoMagicCore * element_core = this->CreateElement(position);
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
