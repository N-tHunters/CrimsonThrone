#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SimpleIni.h>
#include <string>

void LoadConfiguration(std::string);
int GetIntOption(std::string, std::string);
std::string GetStrOption(std::string, std::string);
bool GetBoolOption(std::string, std::string);

void SetIntOption(std::string, std::string, int);
std::string SetStrOption(std::string, std::string, int);

std::string GetDefaultTexture();
int GetBorderWidth();
bool GetMultijump();

#endif
