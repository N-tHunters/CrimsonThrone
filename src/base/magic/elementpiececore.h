#ifndef ELEMENTPIECECORE_H
#define ELEMENTPIECECORE_H

#include "protocore.h"
#include "elementpiece.h"
#include "objectcontrolcore.h"

class ElementPieceCore : public ObjectControlCore {
 public:
  ElementPieceCore(ElementPiece *);
};

#endif
