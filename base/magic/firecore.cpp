#include "firecore.h"
#include "../../render/model.h"
#include "../location.h"
#include "elementpiececore.h"

FireMagicCore::FireMagicCore() : ElementMagicCore() {}

ProtoMagicCore * FireMagicCore::CreateElement(glm::vec3 position) {
  ElementPiece * obj =  new ElementPiece(new Mesh("resources/textures/fire.png", new Model((char *)"resources/models/fireelement.obj")), true, true, false, true, position, glm::vec3(0.0f, 0.0f, 0.0f), "Fire Element");
  ProtoMagicCore * core = (ProtoMagicCore *)new ElementPieceCore(obj);

  GetCurrentLocation()->GetCurrentChunk()->AddObj(obj);
  
  return core;
}
