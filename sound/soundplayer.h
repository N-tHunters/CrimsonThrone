#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <irrKlang.h>

class SoundPlayer {
 private:
  irrklang::ISoundEngine * engine;
 public:
  SoundPlayer();
  irrklang::ISoundEngine * GetEngine();
}

#endif
