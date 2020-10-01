#include "soundplayer.h"

SoundPlayer::SoundPlayer() {
  this->engine = irrklang::createIrrKlangDevice();
}

irrklang::ISoundEngine GetEngine() {
  return this->engine;
}
