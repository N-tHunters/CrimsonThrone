#ifndef CT_FILESOUND_H
#define CT_FILESOUND_H

#include "sound.h"
#include <string>

class FileSound : public Sound {
  std::string filename;
 public:
  FileSound(std::string);
};

#endif
