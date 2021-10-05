#include <render/particleemitter.hpp>


void ParticleEmitter::update(float dt) {
  
  for (unsigned int i = 0; i < 2; ++i) {
    int unusedParticle = firstUnusedParticle();
    respawn(particles[unusedParticle], glm::vec3(0.0f, 0.0f, 0.0f));
  }
  // update all particles
  for (unsigned int i = 0; i < 50; ++i) {
    Particle &p = particles[i];
    p.life -= dt; // reduce life
    if (p.life > 0.0f) {	// particle is alive, thus update
      p.pos -= p.vel * dt;
      p.color.a -= dt * 2.5f;
    }
  }  
}

void ParticleEmitter::init() {
  for (unsigned int i = 0; i < 50; ++i)
    particles.push_back(Particle());
}

void ParticleEmitter::respawn(Particle &particle, glm::vec3 offset) {
  float random = ((rand() % 100) - 50) / 10.0f;
  float rColor = 0.5f + ((rand() % 100) / 100.0f);
  
  particle.pos = target.getPosition() + random + offset;
  particle.color = glm::vec4(rColor, rColor, rColor, 1.0f);
  particle.life = 1.0f;
  particle.vel = target.velocity * 0.1f;
}

unsigned int ParticleEmitter::firstUnusedParticle()
{
  // search from last used particle, this will usually return almost instantly
  for (unsigned int i = lastUsedParticle; i < particles.size(); ++i) {
    if (particles[i].life <= 0.0f){
      lastUsedParticle = i;
      return i;
    }
  }
  // otherwise, do a linear search
  for (unsigned int i = 0; i < lastUsedParticle; ++i) {
    if (particles[i].life <= 0.0f){
      lastUsedParticle = i;
      return i;
    }
  }
  // override first particle if all others are alive
  lastUsedParticle = 0;
  return 0;
} 


void ParticleEmitter::draw(ShaderHolder *shaderHolder, Camera *camera, int width, int height) {
  for (Particle particle : particles) {
    particle.draw(shaderHolder, camera, width, height);
  }
}
