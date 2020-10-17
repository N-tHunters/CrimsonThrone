#include "filesound.h"
#include "load_wav.h"
#include <stdio.h>

FileSound::FileSound(SoundEngine * engine, ALuint * source, std::string filename):
  Sound(engine, source)
{
  this->filename = filename;
  // Init buffer
  alGenBuffers(1, this->GetBufferPtr());
  if(!load_wav_into_buffer(this->filename, this->GetBuffer()))
    std::cerr << "Error while loading wav file" << std::endl;
}

FileSound::FileSound() {}

void FileSound::Play() {
  alSourcei(this->GetSource(), AL_BUFFER, this->GetBuffer());
  alSourcePlay(this->GetSource());
}

void FileSound::PlayToEnd() {
  ALint state = AL_PLAYING;

  this->Play();

  while(state == AL_PLAYING) {
    alGetSourcei(this->GetSource(), AL_SOURCE_STATE, &state);
  }
}

