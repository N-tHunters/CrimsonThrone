#include "configuration.hpp"

CSimpleIniA ini;
std::string default_texture;
int border_width;
bool multijump;

void LoadConfiguration(std::string filename) {
  ini.SetUnicode();
  SI_Error rc = ini.LoadFile(filename.c_str());
  if(rc < 0) printf("Error occured while loading configuration\nError code: %d\n", rc);
  
  default_texture = GetStrOption("Textures", "Default");
  border_width = GetIntOption("UI", "BorderWidth");
  multijump = GetBoolOption("Debug", "Multijump");
}

std::string GetStrOption(std::string section, std::string key) {
  const char * pv = ini.GetValue(section.c_str(), key.c_str(), "");
  return std::string(pv);
}

bool GetBoolOption(std::string section, std::string key) {
  std::string value = GetStrOption(section, key);
  if(value == "YES" || value == "ON")
    return true;
  return false;
}

int GetIntOption(std::string section, std::string key) {
  return std::stoi(GetStrOption(section, key));
}

std::string GetDefaultTexture() {
  return default_texture;
}

int GetBorderWidth() {
  return border_width;
}

bool GetMultijump() {
  return multijump;
}
