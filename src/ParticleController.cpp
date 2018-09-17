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

  repelParticles();

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


void ParticleController::repelParticles() {
    for (auto p1 = mParticles.begin(); p1 != mParticles.end(); ++p1) {
        auto p2 = p1;
        for (++p2; p2 != mParticles.end(); ++p2) {
            vec2 dir = p1->mLoc - p2->mLoc;
            float distance_squared = length2(dir);

            if (distance_squared > 0.0f) {
                vec2 unit_dir = normalize(dir);
                float force = 1.f/distance_squared;
                   p1->mAcc += unit_dir * (force/p1->mMass) - 0.5f * p1->mAcc;
                   p2->mAcc -= unit_dir * (force/p2->mMass) - 0.5f * p2->mAcc;
            }
        }
    }
}