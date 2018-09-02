#include "cinder/app/App.h"
#include "ParticleController.h"
#include <list>
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;


ParticleController::ParticleController(Channel32f channel) :
  mChannel(std::move(channel)),
  mSpacing(1)

{
  mXRes = getWindowWidth() / mSpacing;
  mYRes = getWindowHeight() / mSpacing;
}



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
    it->update(mChannel, mouseLoc);
    ++it;
  }
}


void ParticleController::addParticles(uint amt, const vec2 &loc) {
    for (int i = 0; i < amt; i++) {
        vec2 randVec = Rand::randVec2() * 10.0f;
        mParticles.emplace_back(Particle(randVec + loc));
        addParticle(loc.x, loc.y);
    }
}



void ParticleController::addParticle(float x_i, float y_i) {
  float x_coord = (x_i + 0.5f) * mSpacing;
  float y_coord = (y_i + 0.5f) * mSpacing;

  mParticles.emplace_back(Particle(vec2(x_coord, y_coord)));
}