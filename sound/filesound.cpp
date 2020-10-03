#include "filesound.h"
#include <stdio.h>

FileSound::FileSound(std::string filename) {
  this->filename = filename;
}

void FileSound::Play(irrklang::ISoundEngine *engine) {
  engine->play2D(this->filename.c_str());
}
