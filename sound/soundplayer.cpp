#include "soundplayer.h"


SoundPlayer::SoundPlayer() {
  this->engine = irrklang::createIrrKlangDevice();
}

irrklang::ISoundEngine * SoundPlayer::GetEngine() {
  return this->engine;
}
