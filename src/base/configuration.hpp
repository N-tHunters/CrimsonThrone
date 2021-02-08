#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <Simpleini.h>
#include <string>

void LoadConfiguration(std::string);
int GetIntOption(std::string, std::string);
std::string GetStrOption(std::string, std::string);
void SetIntOption(std::string, std::string, int);
std::string SetStrOption(std::string, std::string, int);

std::string GetDefaultTexture();

#endif
