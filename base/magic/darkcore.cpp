#include "darkcore.h"

DarkMagicCore::DarkMagicCore() : ElementMagicCore() {}

ProtoMagicCore * DarkMagicCore::CreateElement(glm::vec3 position) {
  ElementPiece * obj =  new ElementPiece(new Mesh("resources/textures/dark.png", new Model((char *)"resources/models/darkelement.obj")), true, true, false, true, position, glm::vec3(0.0f, 0.0f, 0.0f), "Dark Element");
  ProtoMagicCore * core = (ProtoMagicCore *)new ElementPieceCore(obj);

  GetCurrentLocation()->GetCurrentChunk()->AddObj(obj);
  
  return core;
}
