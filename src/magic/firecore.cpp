#include "firecore.h"

FireMagicCore::FireMagicCore() : ElementMagicCore() {}

ProtoMagicCore * FireMagicCore::CreateElement(glm::vec3 position) {
  ElementPiece * obj =  new ElementPiece(new Mesh(new Model((char *)"resources/models/fireelement.obj"), get_texture("fire"), 0.2f), true, true, false, true, position, glm::vec3(0.0f, 0.0f, 0.0f), "Fire Element");
  ProtoMagicCore * core = (ProtoMagicCore *)new ElementPieceCore(obj);

  Chunk* chunk_ptr = GetCurrentLocation()->GetCurrentChunk();
  if (chunk_ptr != nullptr) {
  	chunk_ptr->AddObj(obj);
  }
  
  return core;
}
