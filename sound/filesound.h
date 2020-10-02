#ifndef FILESOUND_H
#define FILESOUND_H

#include <string>
#include "sound.h"

class FileSound : public Sound {
 private:
  std::string filename;
 public:
  FileSound(std::string);
  void Play(SoundPlayer *);
};

#endif
