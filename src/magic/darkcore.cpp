#include "darkcore.h"

DarkMagicCore::DarkMagicCore() : ElementMagicCore() {}

ProtoMagicCore * DarkMagicCore::CreateElement(glm::vec3 position) {
  ElementPiece * obj =  new ElementPiece(new Mesh(new Model((char *)"resources/models/darkelement.obj"), get_texture("dark"), 0.2f), true, true, false, true, position, glm::vec3(0.0f, 0.0f, 0.0f), "Dark Element");
  ProtoMagicCore * core = (ProtoMagicCore *)new ElementPieceCore(obj);

  GetCurrentLocation()->GetCurrentChunk()->AddObj(obj);
  
  return core;
}
