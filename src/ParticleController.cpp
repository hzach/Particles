#include "cinder/app/App.h"
#include "ParticleController.h"
#include <list>
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;


ParticleController::ParticleController(Channel32f channel) :
  mChannel(std::move(channel)),
  mSpacing(4)
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
    it -> update(mChannel, mouseLoc);
    ++it;
  }
}



void ParticleController::addParticles_random(int amt) {
  for (int i = 0; i < amt; i++) {
    addParticle();
  }
}



void ParticleController::addParticles_lattice() {
  for (int x = 0; x < mXRes; x++) {
    for (int y = 0; y < mYRes; y++) {
      addParticle(x, y);
    }
  }
}



void ParticleController::addParticle() {
  float xcoord = Rand::randFloat(getWindowWidth());
  float ycoord = Rand::randFloat(getWindowHeight());
  
  mParticles.emplace_back(Particle(vec2(xcoord, ycoord)));
}



void ParticleController::addParticle(int x_i, int y_i) {
  float x_coord = (x_i + 0.5f) * mSpacing;
  float y_coord = (y_i + 0.5f) * mSpacing;

  mParticles.emplace_back(Particle(vec2(x_coord, y_coord)));
}



void ParticleController::removeParticles(int amt) {
  for (int i = 0; i < amt; i++) {
    mParticles.pop_back();
  }
}
