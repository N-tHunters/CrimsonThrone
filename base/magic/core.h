#ifndef MAGIC_CORE_H
#define MAGIC_CORE_H

#include "symbols.h"

enum CORE_STATE {
		 RUNNING,
		 STOPPED_OK,
		 STOPPED_ERROR,
		 DISABLED
};

class MagicCore {
  CORE_STATE state;
 public:
  MaigcCore();
}

#endif
