#ifndef CT_SOUND_H
#define CT_SOUND_H

#include "soundengine.h"

class Sound {
private:
  SoundEngine * engine;
  ALuint * source;
  ALuint buffer;
 public:
  Sound(SoundEngine *, ALuint *);
  virtual void Play();
  SoundEngine * GetEngine();
  ALuint GetBuffer();
  ALuint * GetBufferPtr();
  ALuint GetSource();
  
};

#endif
