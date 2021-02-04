#include "soundengine.h"

SoundEngine::SoundEngine() {
  this->openALDevice = alcOpenDevice(nullptr);
  std::cout << "Creating audio device..." << std::endl;
  if(!this->openALDevice) {
    std::cerr << "Error while initializing sound device" << std::endl;
    return;
  }
  this->openALContext = alcCreateContext(this->openALDevice, nullptr);
  if(!this->openALContext) {
    std::cerr << "ERROR: Could not create audio context" << std::endl;
    return;
  }
  ALCboolean contextMadeCurrent = alcMakeContextCurrent(this->openALContext);
  if(contextMadeCurrent != ALC_TRUE) {
    std::cerr << "ERROR: Could not make audio context current" << std::endl;
    return;
  }
}

SoundEngine::~SoundEngine() {
  alcMakeContextCurrent(this->openALContext);
  alcDestroyContext(this->openALContext);
  alcCloseDevice(this->openALDevice);
}
