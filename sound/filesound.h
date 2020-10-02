#ifndef FILESOUND_H
#define FILESOUND_H

#include <string>
#include "sound.h"
#include <irrklang/irrKlang.h>

class FileSound : public Sound {
 private:
  std::string filename;
  bool loop;
 public:
  FileSound(std::string);
  FileSound(std::string, bool);
  void Play(irrklang::ISoundEngine *);
};

#endif
