#include "voice.h"
#include <unistd.h>

Voice::Voice(SoundEngine * engine, ALuint * source, std::string voice_path) {
  this->engine = engine;
  this->source = source;
  this->voice_path = voice_path;

  for(int i = 0; i < 26; i ++) {
    char letter = 'a' + i;
    std::string letter_path = this->voice_path + letter + ".wav";
    this->sounds[i] = FileSound(this->engine, this->source, letter_path);
  }
}


void Voice::Say(std::string phrase) {
  for(size_t i = 0; i < phrase.size(); i ++) {
    if(phrase[i] == ' ') {
      sleep(0.5);
    } else 
      this->sounds[phrase[i] - 'a'].PlayToEnd();
  }
}
