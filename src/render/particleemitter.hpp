#pragma once

#include <render/particle.hpp>
#include <vector>
#include <physics/physicalObj.hpp>


class ParticleEmitter {
  PhysicalObj &target;
  std::vector<Particle> particles;
  unsigned int lastUsedParticle = 0;

  ParticleEmitter(PhysicalObj &target):
    target(target) { init(); }

  void update(float dt);
  void respawn(Particle &particle, glm::vec3 offset);
  unsigned int firstUnusedParticle();
  void init();
  void draw(ShaderHolder *, Camera *, int, int);
};
