#include "voidcore.h"

VoidMagicCore::VoidMagicCore() : ElementMagicCore() {}

ProtoMagicCore * VoidMagicCore::CreateElement(glm::vec3 position) {
  ElementPiece * obj =  new ElementPiece(new Mesh(new Model((char *)"resources/models/voidelement.obj"), get_texture("void")), true, true, false, true, position, glm::vec3(0.0f, 0.0f, 0.0f), "Void Element");
  ProtoMagicCore * core = (ProtoMagicCore *)new ElementPieceCore(obj);

  GetCurrentLocation()->GetCurrentChunk()->AddObj(obj);
  
  return core;
}
