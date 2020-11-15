#include "firecore.h"
#include "../../render/model.h"

FireMagicCore::FireMagicCore() : ElementMagicCore() {}

ProtoMagicCore * FireMagicCore::CreateElement(glm::vec3 position) {
  PhysicalObj * obj =  new PhysicalObj(new Mesh("resources/textures/fire.png", new Model((char *)"resources/models/firelement.obj")), true, true, false, position, glm::vec3(0.0f, 0.0f, 0.0f), "Fire Element");
  ProtoMagicCore * core = new ProtoMagicCore(obj);
  return core;
}
