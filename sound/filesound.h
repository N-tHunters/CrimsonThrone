#ifndef CT_FILESOUND_H
#define CT_FILESOUND_H

#include "sound.h"
#include <string>

class FileSound : public Sound {
private:
  std::string filename;
 public:
  FileSound(SoundEngine*, ALuint *, std::string);
  void Play();
};

#endif
