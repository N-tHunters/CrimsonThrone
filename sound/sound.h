#ifndef CT_SOUND_H
#define CT_SOUND_H

#include <irrklang/IrrKlang.h>

class Sound {
 public:
  virtual void Play(irrklang::ISoundEngine *);
};

#endif
