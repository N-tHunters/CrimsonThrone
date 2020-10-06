#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H


// OpenAL related code ----------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <ostream>
#include <AL/al.h>
#include <AL/alc.h>

class SoundEngine {
 private:
  ALCdevice *openALDevice;
  ALCcontext *openALContext;
 public:
  SoundEngine();
};

#endif
