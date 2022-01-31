#pragma once

#include <render/particle.hpp>
#include <vector>
#include <physics/physicalObj.hpp>


class ParticleEmitter {
  PhysicalObj &target;
  std::vector<Particle> particles;
  unsigned int lastUsedParticle = 0;

  GLuint texture;

public:
  ParticleEmitter(PhysicalObj &target, GLuint texture):
    target(target), texture(texture) { init(); }

  void update(float dt);
  void respawn(Particle &particle, glm::vec3 offset);
  unsigned int firstUnusedParticle();
  void init();
  void draw(Camera *);
};
