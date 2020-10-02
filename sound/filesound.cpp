#include "filesound.h"

FileSound::FileSound(std::string filename) :
  FileSound(filename, false) {}


FileSound::FileSound(std::string filename, bool loop) {
  this->filename = filename;
  this->loop = loop;
}

void FileSound::Play(irrklang::ISoundEngine * engine) {
  engine->play2D(this->filename.c_str(), this->loop);
}
