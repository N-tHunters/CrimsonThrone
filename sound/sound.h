#ifndef SOUND_H
#define SOUND_H

#include "soundplayer.h"

class Sound {
 public:
  virtual void Play(SoundPlayer *);
};

#endif
