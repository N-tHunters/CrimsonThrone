#ifndef VOICE_H
#define VOICE_H

#include "filesound.h"
#include "soundengine.h"

class Voice {
 private:
  SoundEngine * engine;
  ALuint * source;
  std::string voice_path;
  FileSound sounds[26];
 public:
  Voice(SoundEngine *, ALuint *, std::string);
  void Say(std::string);
};

#endif
