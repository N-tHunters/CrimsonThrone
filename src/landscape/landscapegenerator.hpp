#ifndef LANDSCAPEGENERATOR_H
#define LANDSCAPEGENERATOR_H

#include <stddef.h>
#include <string>
#include <physics/physicalObj.hpp>

class Location;

class LandscapeGenerator {
public:
  LandscapeGenerator();
  virtual void Generate(Location *, size_t, size_t, int, int, int);
};

PhysicalObj * create_wall(glm::vec3, glm::vec3, std::string);

#endif
