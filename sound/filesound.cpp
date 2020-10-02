#include "filesound.h"

FileSound::FileSound(std::string filename) {
  this->filename = filename;
}

void FileSound::Play(SoundPlayer * player) {
  player->GetEngine()->play2D(this->filename.c_str());
}
