#include "configuration.hpp"

CSimpleIniA ini;
std::string default_texture;

void LoadConfiguration(std::string filename) {
  ini.SetUnicode();
  SI_Error rc = ini.LoadFile(filename.c_str());
  if(rc < 0) printf("Error occured while loading configuration\nError code: %d\n", rc);
  
  default_texture = GetStrOption("Textures", "Default");
}

std::string GetStrOption(std::string section, std::string key) {
  const char * pv = ini.GetValue(section.c_str(), key.c_str(), "");
  return std::string(pv);
}

std::string GetDefaultTexture() {
  return default_texture;
}

