#include "voidcore.h"
#include "../../render/model.h"
#include "../location.h"
#include "elementpiececore.h"

VoidMagicCore::VoidMagicCore() : ElementMagicCore() {}

ProtoMagicCore * VoidMagicCore::CreateElement(glm::vec3 position) {
  ElementPiece * obj =  new ElementPiece(new Mesh("resources/textures/void.png", new Model((char *)"resources/models/voidelement.obj")), true, true, false, position, glm::vec3(0.0f, 0.0f, 0.0f), "Void Element");
  ProtoMagicCore * core = (ProtoMagicCore *)new ElementPieceCore(obj);

  GetCurrentLocation()->GetCurrentChunk()->AddObject(obj);
  
  return core;
}
