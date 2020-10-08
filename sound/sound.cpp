#include "sound.h"

Sound::Sound(SoundEngine * engine, ALuint * source) {
  this->engine = engine;
  this->source = source;
}

Sound::Sound() {}

void Sound::Play() {}
void Sound::PlayToEnd() {}

SoundEngine * Sound::GetEngine() {
  return this->engine;
}

ALuint Sound::GetBuffer() {
  return this->buffer;
}

ALuint * Sound::GetBufferPtr() {
  return &this->buffer;
}

ALuint Sound::GetSource() {
  return *this->source;
}
