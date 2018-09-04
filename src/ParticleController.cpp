#include "cinder/app/App.h"
#include "ParticleController.h"
#include <list>
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;


ParticleController::ParticleController(Channel32f channel) :
  mChannel(std::move(channel)),
  mSpacing(1),
  mPerlin()
{}



void ParticleController::draw() {
  std::list<Particle>::iterator it;
  it = mParticles.begin();

  while (it != mParticles.end()) {
    it -> draw();
    ++it;
  }
}



void ParticleController::update(const vec2 mouseLoc) {
  std::list<Particle>::iterator it;
  it = mParticles.begin();

  while (it != mParticles.end()) {
      if (it->mIsDead) {
          it = mParticles.erase(it);
      } else {
          it->update(mChannel, mouseLoc, mPerlin);
          ++it;
      }
  }
}


void ParticleController::addParticles(uint amt, const vec2 &loc, const vec2 &vel) {
    for (int i = 0; i < amt; i++) {
        vec2 randVec = Rand::randVec2() * 0.25f;
        vec2 vel_offset = Rand::randVec2() * Rand::randFloat(1.0f, 3.0f);
        mParticles.emplace_back(Particle(randVec + loc, vel + vel_offset));
    }
}