#ifndef SOUND_H
#define SOUND_H

#include <irrklang/irrKlang.h>

class Sound {
 public:
  virtual void Play(irrklang::ISoundEngine *);
};

#endif
