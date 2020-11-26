#ifndef ELEMENTPIECECORE_H
#define ELEMENTPIECECORE_H

#include "protocore.h"
#include "elementpiece.h"

class ElementPieceCore : public ProtoMagicCore {
 private:
 public:
  ElementPieceCore(ElementPiece *);
  char SetVelocity(char arg, AbstractCore *core);
  char Call(char id, char arg, AbstractCore *core);
};

#endif
